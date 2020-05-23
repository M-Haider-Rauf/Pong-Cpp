#ifndef BALL_HPP
#define BALL_HPP

#include <random>
#include "GameObject.hpp"
#include "Bat.hpp"

constexpr float BALL_SPEED = 15.f;

class Ball : public GameObject {
public:
//----------------------------------------------
//Ctors
	Ball(float = 0.f);

//----------------------------------------------
//Collision Functions
	bool in_bounds() const;
	bool check_bat_collision(const Bat&) const;
	unsigned check_lost() const;
	void randomize_velocity();
	void handle_collisions(const Bat&, const Bat&);
	void reset_position(bool flag);

//----------------------------------------------
//Overriding pure virtual function draw()
	void draw() const override;

private:
	float radius;
};

#endif // !BALL_HPP
