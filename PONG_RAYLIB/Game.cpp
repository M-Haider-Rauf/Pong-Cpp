#include "Game.hpp"

//about text
const char* Game::about_text =
"Hello! It's Haider in March 2020.\n"
"I was bored as fuck in Quarantine so\n"
"I did what any completely normal human\n"
"being would do i.e. code.\n"
"I had a lot of fun in coding this, \n"
"even though it's not much.\n\n"
"Anyways, press ENTER to go back to Menu.\n";


Game::Game()
	: menu()
	, game_state(GameState::Null)
	, bat1(BAT_SIZE)
	, bat2(BAT_SIZE)
	, ball(7.f)
	, score1(0)
	, score2(0)
	, quit(false)
{
	static constexpr float bat_off = 20.f;
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Pong by Haider");
	SetTargetFPS(30);

	//SetBat1InitialPosition
	bat1.set_position({BORDER_SIZE + bat_off, WIN_HEIGHT / 2.f});
	bat1.set_color(BLUE);
	bat1.set_velocity({ BAT_SPEED, BAT_SPEED });

	//SetBat2InitialPosition
	bat2.set_position({ WIN_WIDTH - BORDER_SIZE - bat_off - bat2.get_dimensions().x,
						 WIN_HEIGHT / 2.f });
	bat2.set_color(GREEN);
	bat2.set_velocity({ BAT_SPEED, BAT_SPEED });

	//Ball
	ball.reset_position(1);
	ball.set_color(MAGENTA);
	ball.randomize_velocity();

	game_state = GameState::Menu;
}

Game* Game::get_instance()
{
	static Game game;
	return &game;
}

Game::~Game()
{
}

//-------------------------------------------------------------
//Main Loop that does everything

void Game::main_loop()
{
	while (!WindowShouldClose() && !quit) {
		handle_events();
		update();
		render();
	}
}



//-------------------------------------------------------------
//Top-Level functions that

void Game::handle_events()
{
	switch (game_state) {
	case GameState::Null:
		break;

	case GameState::Playing:
		handle_game_events();
		break;

	case GameState::Waiting:
		handle_waiting_events();
		break;

	case GameState::Paused:
		handle_paused_events();
		break;

	case GameState::Menu:
		handle_menu_events();
		break;

	case GameState::About:
		handle_about_events();
		break;

	case GameState::Win:
		handle_win_events();
		break;

	default:
		break;
	}
}


void Game::update()
{
	switch (game_state) {
	case GameState::Null:
		break;

	case GameState::Playing:
		update_game();
		break;

	case GameState::Waiting:
		break;

	case GameState::Paused:
		break;

	case GameState::Menu:
		break;

	default:
		break;
	}
}


void Game::render() const
{
	BeginDrawing();
	ClearBackground(BLACK);

	switch (game_state) {
	case GameState::Null:
		break;
	case GameState::Playing:
		render_game();
		break;
	case GameState::Waiting:
		render_waiting();
		break;
	case GameState::Paused:
		render_paused();
		break;

	case GameState::About:
		render_about();
		break;

	case GameState::Win:
		render_win();
		break;

	case GameState::Menu:
		render_menu();
		break;

	default:
		break;
	}
	EndDrawing();
}

void Game::reset_game()
{
	bat1.reset_position();
	bat2.reset_position();
	ball.reset_position(0);
	score1 = score2 = 0;
}



//---------------------------------------------------------------
//Game Functions---

void Game::handle_game_events()
{
	bat1.set_direction(Direction::None);
	bat2.set_direction(Direction::None);
	if (IsKeyDown(KEY_UP)) {
		bat1.set_direction(Direction::Up);
		bat2.set_direction(Direction::Up);
			
	}
	if (IsKeyDown(KEY_DOWN)) {
		bat1.set_direction(Direction::Down);
		bat2.set_direction(Direction::Down);
	}
	if (IsKeyDown(KEY_P)) {
		game_state = GameState::Paused;
	}

}


void Game::update_game()
{
	if (bat1.check_bounds()) {
		bat1.move_in_direction(bat1.get_direction(), bat1.get_velocity().x);
	}
	if (bat2.check_bounds()) {
		bat2.move_in_direction(bat1.get_direction(), bat1.get_velocity().x);
	}
	ball.move();
	ball.handle_collisions(bat1, bat2);

	unsigned lost = ball.check_lost();
	if (lost) {
		bat1.reset_position();
		bat2.reset_position();
		game_state = GameState::Waiting;
		ball.invert_x_velocity();
	}

	if (lost == 1) {
		ball.reset_position(1);
		++score1;
	}
	else if (lost == 2) {
		ball.reset_position(0);
		++score2;
	}

	if (score1 >= WIN_SCORE || score2 >= WIN_SCORE) {
		game_state = GameState::Win;
	}

}


void Game::render_game() const
{
	draw_score();
	bat1.draw();
	bat2.draw();
	ball.draw();
	draw_borders(BORDER_SIZE);
	draw_dashed_line();
}


//--------------------------------------------------------
//Waiting functions;

void Game::render_waiting() const
{
	render_game();
	DrawText("PRESS S TO START", 250, 200, 32, DARKBLUE);
}


void Game::handle_waiting_events()
{
	if (IsKeyPressed(KEY_S)) {
		game_state = GameState::Playing;
	}
}

//---------------------------------------------------------
//Paused Functions
void Game::render_paused() const
{
	render_game();
	DrawText("PAUSED!\nPRESS R TO RESUME", 300, 200, 32, DARKBLUE);
}


void Game::handle_paused_events()
{
	if (IsKeyPressed(KEY_R)) {
		game_state = GameState::Playing;
	}
}

//---------------------------------------------------------
//Menu Functions
void Game::render_menu() const
{
	menu.draw();
}

void Game::handle_menu_events()
{
	size_t selected = menu.current_option();
	if (IsKeyPressed(KEY_ENTER)) {
		switch (selected)
		{
		case 0:
			game_state = GameState::Waiting;
			break;

		case 1:
			game_state = GameState::About;
			break;

		case 2:
			quit = true;
			break;

		default:
			break;
		}
	}

	if (IsKeyPressed(KEY_UP)) menu.move_up();
	if (IsKeyPressed(KEY_DOWN)) menu.move_down();
}


//----------------------------------------------------------
//About screen
void Game::render_about() const
{
	DrawText(about_text, 80, 100, 30, DARKBLUE);
}

void Game::handle_about_events()
{
	if (IsKeyPressed(KEY_ENTER)) game_state = GameState::Menu;
}


//------------------------------------------------------------
//Win Screen
void Game::render_win() const
{
	size_t win_player = score1 > score2 ? 2 : 1;

	DrawText(FormatText("Player %u won!\nPress R to restart\n...Or ESCAPE to Quit", win_player),
		220, 200, 40, RED);
}


void Game::handle_win_events()
{
	if (IsKeyPressed(KEY_R)) {
		this->reset_game();
		game_state = GameState::Waiting;
	}

	if (IsKeyPressed(KEY_ESCAPE)) {
		quit = true;
	}
}


//---------------------------------------------------------
//help drawing
void Game::draw_borders(float thickness) const	//Draw all borders
{
	static const Rectangle borders [] {
		{0.f, 0.f, WIN_WIDTH, thickness},	//top
		{0.f, WIN_HEIGHT - thickness, WIN_WIDTH, thickness},	//bottom
		{0.f, 0.f, thickness, WIN_HEIGHT},	//left
		{WIN_WIDTH - thickness, 0.f, thickness, WIN_HEIGHT}
	};

	for (size_t i = 0; i < 4; ++i) {
		DrawRectangleRec(borders[i], RED);
	}
}

void Game::draw_score() const
{
	static constexpr float yOff = BORDER_SIZE + 2.f;
	static constexpr float score2_pos = WIN_WIDTH / 2.f - 50.f;
	static constexpr float score1_pos = WIN_WIDTH / 2.f + 30.f;

	DrawText(TextFormat("%u", score1), score1_pos, yOff, 40, RED);
	DrawText(TextFormat("%u", score2), score2_pos, yOff, 40, RED);

}

void Game::draw_dashed_line() const
{
	static constexpr float LINE_SEPARATION = 5.f;
	static constexpr float LINE_WIDTH = 2.f;

	Vector2 begin{WIN_WIDTH / 2.f, 0.f};
	Vector2 end{WIN_WIDTH / 2.f, LINE_SEPARATION};

	while (end.y <= WIN_HEIGHT) 
	{
		DrawLineEx(begin, end, LINE_WIDTH, RED);
		begin.y += 2 * LINE_SEPARATION;
		end.y += 2 * LINE_SEPARATION;
	}
}

//------------------------------------------------------------------
//Todo Functions?

