#ifndef FLOAT_OBJ_H
#define FLOAT_OBJ_H

#include "main.h"
#include "shapes.h"
#include "object.h"

class Arrow{
public:
	Arrow();
	Object arrow;
	mat4 MVP;
	bool move = true;

	void create_arrow();
	void render_arrow(GLuint);
	void move_arrow();
	void disappear();
};

class Fuel{
public:
	Fuel();
	Object fuel;
	mat4 MVP;

	void create_fuel();
	void render_fuel(GLuint);
	void rotate_fuel(mat4);
};

class Ring{
public:
	Ring();
	Object ring;
	mat4 MVP;

	void create_ring();
	void render_ring(GLuint);
};

class Coin{
public:
	Coin();
	Object coin;
	mat4 MVP;

	void create_coin();
	void render_coin(GLuint);
};

#endif