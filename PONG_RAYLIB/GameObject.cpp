#include "GameObject.hpp"


//---------------------------------------
//Ctors and Dtors etc.
GameObject::GameObject()	//default initialize to sensible values..
	: position ({0, 0})
	, velocity ({0, 0})
	, origin ({0, 0})
	, color (BLACK)
{
}

//-----------------------------------------------
//Velocity Functions
void GameObject::set_velocity(const Vector2& velocity)
{
	this->velocity = velocity;
}


Vector2 GameObject::get_velocity() const
{
	return velocity;
}


void GameObject::invert_x_velocity()
{
	velocity.x = -velocity.x;
}


void GameObject::invert_y_velocity()
{
	velocity.y = -velocity.y;
}


//----------------------------------------------------
//Position Functions
void GameObject::set_position(const Vector2& position)
{
	this->position = position;
}

Vector2 GameObject::get_position() const
{
	return position;
}


//---------------------------------------------------
//Movement Functions
void GameObject::move(const Vector2& dv)
{
	position.x += dv.x;
	position.y += dv.y;
}

void GameObject::move()
{
	move(velocity);
}

void GameObject::move_in_direction(Direction direction, float speed)
{
	switch (direction)
	{
	case Direction::None:
		break;

	case Direction::Left:
		position.x -= speed;
		break;

	case Direction::Right:
		position.x += speed;
		break;

	case Direction::Up:
		position.y -= speed;
		break;

	case Direction::Down:
		position.y += speed;
		break;

	default:
		TraceLog(LOG_ERROR, "Why is it here? (direction defaulted)\n");
		break;
	}

	return;
}

//------------------------------------------------------
//color funtions

void GameObject::set_color(Color color)
{
	this->color = color;
}
