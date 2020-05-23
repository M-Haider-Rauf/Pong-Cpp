#include "Menu.hpp"

//---------------------------------------------
//Ctors

Menu::Menu() : texts(), state(0), option_color(RED), selected_color(SKYBLUE)
{
	texts.push_back("Play");
	texts.push_back("About");
	texts.push_back("Quit");
}


//---------------------------------------------

void Menu::move_up()
{
	--state;
}

void Menu::move_down()
{
	++state;
}

size_t Menu::current_option() const
{
	return state % texts.size();
}


//--------------------------------------------

void Menu::draw() const
{
	draw_title();
	size_t selected = current_option();

	for (size_t i = 0; i < texts.size(); ++i) {
		Color text_color = { 0 };
		if (i == selected) {
			text_color = this->selected_color;
		} 
		else {
			text_color = this->option_color;
		}
		DrawText(texts[i].c_str(), TITLE_X, TITLE_Y + (i + 1) * TEXT_PADDING + TITLE_SIZE,
			TEXT_SIZE, text_color);
	}
}


//--------------------------------------------
void Menu::draw_title() const
{
	DrawText("PONG!", TITLE_X, TITLE_Y, TITLE_SIZE, RED);
	DrawText("by HaiderRauf69", TITLE_X + 60.f, TITLE_Y + TITLE_SIZE, 20, YELLOW);
}


