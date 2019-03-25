#ifndef WEAPONS_H
#define WEAPONS_H

#include "main.h"
#include "object.h"
#include "shapes.h"

class Missile{
public:
	Missile();
	Missile(float x, float y, float z);
	Object missile;

	GLuint uvbuffer;
	GLuint normbuffer;
	GLuint Texture;
	GLuint TextureID;
	bool p_fired = false;
	bool s_fired = false;
	float t = 0;

	void create_missile(const char*, const char*, GLuint);
	void render_missile();
	void fire();
	void plane_fire();
	void ship1_fire(vec3);
	void ship2_fire(vec3);
	void ship3_fire(vec3);
};

class Bomb{
public:

	Bomb(float x, float y, float z);
	Object bomb;

	GLuint uvbuffer;
	GLuint normbuffer;
	GLuint Texture;
	GLuint TextureID;
	bool fired = false;

	void create_bomb(const char*, const char*, GLuint);
	void render_bomb();
	void fire();

};


#endif