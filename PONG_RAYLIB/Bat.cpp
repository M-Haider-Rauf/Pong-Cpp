#include "Bat.hpp"


//----------------------------------------------------------
//Ctors
Bat::Bat(const Vector2& dimensions)
	: dimensions (dimensions)
	, direction (Direction::None)
{
}



//----------------------------------------------------------
//Direction Functions
Direction Bat::get_direction() const
{
	return direction;
}

void Bat::reset_position()
{
	const float xPos = get_position().x;
	set_position({ xPos, WIN_HEIGHT / 2.f });
}

void Bat::set_direction(Direction direction)
{
	this->direction = direction;
}


//-------------------------------------------------------------
//Check moving bounds
bool Bat::check_bounds() const
{
	Vector2 position = get_position();
	//position.y += dimensions.y;
	static constexpr float off = 7.f;

	if ((position.y <= BORDER_SIZE + off && 
		direction == Direction::Up) ||
		(position.y + dimensions.y >= WIN_HEIGHT - BORDER_SIZE - off && 
			direction == Direction::Down)) {
		return false;
	}
	else {
		return true;
	}
}


//----------------------------------------------------------------
//overriding pure virtual draw()
void Bat::draw() const
{
	DrawRectangleV(get_position(), dimensions, get_color());
}
