#ifndef BAT_HPP
#define BAT_HPP

#include "GameObject.hpp"
#include "GameConstants.hpp"

class Bat : public GameObject {
public:
//--------------------------------------------------------
//Ctors
	Bat(const Vector2& = {0.f, 0.f});

//--------------------------------------------------------
//Direction management functions
	void set_direction(Direction direction);
	Direction get_direction() const;
	void reset_position();

//--------------------------------------------------------
//Dimension function
	void set_dimensions(const Vector2& dimensions) { this->dimensions = dimensions; }
	Vector2 get_dimensions() const { return dimensions; }


//Check moving bounds
	bool check_bounds() const;


//--------------------------------------------------------
//Overriding draw()
	void draw() const override;


private:
	Vector2 dimensions;
	Direction direction;
};

#endif // !BAT_HPP
