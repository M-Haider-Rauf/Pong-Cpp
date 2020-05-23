#include "Ball.hpp"


//------------------------------------
//Ctors
Ball::Ball(float radius) : radius(radius)
{
}


//----------------------------------------
//collision functions

bool Ball::in_bounds() const
{
	const Vector2 position = get_position();
	const Vector2 velocity = get_velocity();
	if ((position.y <= radius + BORDER_SIZE && velocity.y < 0.f) ||
		(position.y >= WIN_HEIGHT - radius - BORDER_SIZE && velocity.y > 0.f)) {
		return false;
	}
	return true;
}


bool Ball::check_bat_collision(const Bat& bat) const
{
	const Rectangle bat_rec {
		bat.get_position().x, bat.get_position().y,
		bat.get_dimensions().x, bat.get_dimensions().y
	};

	return CheckCollisionCircleRec(get_position(), radius, bat_rec);
}


unsigned Ball::check_lost() const
{
	const Vector2 position = get_position();

	if (position.x < BORDER_SIZE) {
		return 1;
	}
	/*else*/ if (position.x > WIN_WIDTH - BORDER_SIZE) {
		return 2;
	}
	return 0;
}

void Ball::randomize_velocity()
{
	static std::random_device rd;
	static std::uniform_real_distribution<float> dist(BALL_SPEED * 0.28f, BALL_SPEED * 0.72f);
	static std::default_random_engine rand_eng(rd());

	const Vector2 old_velocity = get_velocity();
	Vector2 new_velocity;
	new_velocity.x = dist(rand_eng);
	new_velocity.y = BALL_SPEED - new_velocity.x;

	if (old_velocity.x < 0) new_velocity.x *= -1.f;
	if (old_velocity.y < 0) new_velocity.y *= -1.f;

	this->set_velocity(new_velocity);
}

void Ball::handle_collisions(const Bat& bat1, const Bat& bat2)
{
	const auto velocity = get_velocity();

	if (!in_bounds()) {
		this->invert_y_velocity();
		this->randomize_velocity();
	}

	if ((check_bat_collision(bat1) && velocity.x < 0.f) || 
		(check_bat_collision(bat2) && velocity.x > 0.f)) {
		this->invert_x_velocity();
		this->randomize_velocity();
	}
}


//flag controls ball_side, true = right, false = left
//ikr crappy stupid logic but what can you do
void Ball::reset_position(bool flag)
{
	if (flag) {
		set_position({ 80.f,  WIN_HEIGHT / 2.f});
	}
	else {
		set_position({ WIN_WIDTH - 80.f, WIN_HEIGHT / 2.f });
	}

}


//--------------------------------------
void Ball::draw() const 
{
	DrawCircleV(get_position(), radius, get_color());
}
