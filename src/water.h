#ifndef WATER_H
#define WATER_H

#include "main.h"
#include "shapes.h"
#include "object.h"

class Water{
public:
	Water();
	Water(float x, float y, float z);
	Object sea;

	void create_water();
	void render_water(GLuint, mat4);
};

#endif