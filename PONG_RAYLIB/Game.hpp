#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <iostream>
#include "GameConstants.hpp"
#include "Bat.hpp"
#include "Ball.hpp"
#include "Menu.hpp"

#define WIN_SCORE 10
#define BAT_SPEED 7.5f

enum struct GameState {
	Null, Playing, Waiting, Paused, Menu, About, Win
};

//----------------------------------------------------
//Main game class that takes care of standard event-update-render 
//loop. It's been implemented using the Singleton Pattern
class Game {
public:
//----------------------------------------------------
//Ctor and Dtor
	static Game* get_instance();
	static void cleanup() { delete instance; instance = nullptr; }
	~Game();
//----------------------------------------------------
//Deleted assignemnet and cpy ctor-doesn't really make sense to copy a game...
	Game(const Game&) = delete;
	Game& operator= (const Game&) = delete;
//----------------------------------------------------
//main_loop that does everything;
	void main_loop();

//----------------------------------------------------


private:
	//-------------------------------------------------
	//Top-Level Functions for updating, rendering appropriate systems etc.
	void handle_events();
	void update();
	void render() const;
	void reset_game();

	//------------------------------------------------
	//Game Functions
	void handle_game_events();
	void update_game();
	void render_game() const;	
	Game();

	//--------------------------------------------------
	//Paused Functions
	void render_paused() const;
	void handle_paused_events();


	//---------------------------------------------------
	//Waiting Funtions
	void render_waiting() const;
	void handle_waiting_events();

	//-------------------------------------------------
	//Menu Functions
	void render_menu() const;
	void handle_menu_events();


	//-------------------------------------------------
	//About screen events
	void render_about() const;
	void handle_about_events();

	//------------------------------------------------
	//Win Screen functions
	void render_win() const;
	void handle_win_events();

	//------------------------------------------------
	//Drawing helping functions
	void draw_dashed_line() const;
	void draw_borders(float) const;
	void draw_score() const;

	//------------------------------------------------
	//Private variables
	Menu menu;
	GameState game_state;
	Bat bat1;
	Bat bat2;
	Ball ball;
	unsigned score1;
	unsigned score2;
	bool quit;

	static const char* about_text;

	static Game* instance;
};


#endif // !GAME_HPP
