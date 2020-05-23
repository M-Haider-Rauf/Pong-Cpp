#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <raylib.h>

#include "GameConstants.hpp"

#define TITLE_SIZE 80
#define TITLE_X 300 
#define TITLE_Y 80
#define TEXT_PADDING 70
#define TEXT_SIZE 40

class Menu {
public:
	Menu();

	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;	//Because, why'd you ever wanna copy a menu?

	void move_up();
	void move_down();

	size_t current_option() const;
	void draw() const;

private:
	void draw_title() const;

	std::vector<std::string> texts;  
	size_t state;

	Color option_color;
	Color selected_color;
};


#endif // !MENU_HPP
