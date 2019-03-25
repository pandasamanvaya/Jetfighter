#ifndef ISLAND_H
#define ISLAND_H

#include "main.h"
#include "shapes.h"
#include "object.h"

class Island{
public:

	Island();
	GLuint colorbuffer;

	Object isld;
	void create_island();
	void render_island(GLuint, mat4);
};

#endif