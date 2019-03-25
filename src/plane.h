#ifndef PLANE_H
#define PLANE_H

#include "main.h"
#include "object.h"
#include "shapes.h"
#include "weapons.h"

extern float depth;

class Aim{
public:
	Aim();
	Object aim;

	void create_aim();
	void render_aim(GLuint, mat4);
};

class Plane : public Aim{
public:
	Plane();
	Plane(float x, float y, float z);
	Object plane;
	Bomb bmb = Bomb(0.0, depth - 5, 0.0);
	Missile missl = Missile(0.0, depth - 5, 0.0);

	GLuint uvbuffer;
	GLuint normbuffer;
	GLuint Texture;
	GLuint TextureID;
	float r_angle = 0.0, y_angle = 0.0, speed_x, speed_z, fact = 0.3;

	void create_plane(const char*, const char*, GLuint);
	void bindbuffer(vector<vec3>, vector<vec2>, vector<vec3>);
	void render_plane(GLuint, mat4);
	void bindTexture();
	void move_plane();
	void moveup();
	void fall();
	//void fire_bomb();
	void fire_missile();
};

#endif