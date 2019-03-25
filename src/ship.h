#ifndef SHIP_H
#define SHIP_H

#include "main.h"
#include "object.h"
#include "float_obj.h"
#include "weapons.h"

extern float depth;

class Ship{
public:
	Ship();
	Ship(float x, float y, float z);
	Object ship;
	Arrow arrow;
	Missile missl = Missile(ship.position.x, ship.position.y, ship.position.z);
	bool dead = false;
	
	GLuint uvbuffer;
	GLuint normbuffer;
	GLuint Texture;
	GLuint TextureID;

	void create_ship(const char*, const char*, GLuint);
	void bindbuffer(vector<vec3>, vector<vec2>, vector<vec3>);
	void render_ship(GLuint);
	void bindTexture();
	void destroyed();
	void fire_missile(vec3);
};

#endif