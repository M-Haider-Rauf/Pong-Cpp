#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
//GameObject is the base class for all (get this) game objects....
//This class is abstract

#include <raylib.h>


enum struct Direction {
	None, Left, Right, Up, Down
};

class GameObject {
public:
	//----------------------------------------
	//Ctors and Dtors etc.
	GameObject();
	virtual ~GameObject() = default;

	//-----------------------------------------
	//Velocity Functions
	void set_velocity(const Vector2&);
	Vector2 get_velocity() const;

	void invert_x_velocity();
	void invert_y_velocity();

	//------------------------------------------
	//Position functions
	void set_position(const Vector2&);
	Vector2 get_position() const;


	//--------------------------------------------
	//Movement Functions
	void move(const Vector2&);
	void move();
	void move_in_direction(Direction, float);

	//----------------------------------------------
	//Color functions
	void set_color(Color);
	Color get_color() const { return color; }

	//----------------------------------------
	//pure virtual method for drawing, since every object has its's own drawing method
	virtual void draw() const = 0;

private:
	Vector2 position;
	Vector2 velocity;
	Vector2 origin;
	Color color;
};

#endif // !GAMEOBJECT_HPP
