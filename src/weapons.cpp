#include "weapons.h"
#include "plane.h"
#include "ship.h"

extern Plane jet;
extern float depth;
float g = 0.5;
extern Ship ship1, ship2, ship3;

//Bomb
Bomb :: Bomb(float x, float y, float z)
{
	this -> bomb.position = vec3(x, y, z);
}

void Bomb :: create_bomb(const char *texfile, const char *objfile, GLuint programID)
{
	this -> Texture = loadBMP_custom(texfile);
	this -> TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals; 

	bool res = loadOBJ(objfile, vertices, uvs, normals);

	this -> bomb.len = vertices.size();
	bomb.bind_vertbuffer(&(this->bomb.vertexbuffer), vertices);
	bomb.bind_uvbuffer(&(this->uvbuffer), uvs);
	bomb.bind_normbuffer(&(this->normbuffer), normals);

}

void Bomb :: render_bomb()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this -> Texture);
	glUniform1i(this -> TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->bomb.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, this -> bomb.len);

	if(this -> fired)
		this -> fire();
	this -> bomb.unbind_vertex_buffer();

}

void Bomb :: fire()
{	
	if(bomb.position.y > depth)
		this -> bomb.position.y -= g;
}

//Missile
Missile :: Missile(float x, float y, float z)
{
	this -> missile.position = vec3(x, y, z);

}

void Missile :: create_missile(const char *texfile, const char *objfile, GLuint programID)
{
	this -> Texture = loadBMP_custom(texfile);
	this -> TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals; 

	bool res = loadOBJ(objfile, vertices, uvs, normals);

	this -> missile.len = vertices.size();
	missile.bind_vertbuffer(&(this->missile.vertexbuffer), vertices);
	missile.bind_uvbuffer(&(this->uvbuffer), uvs);
	missile.bind_normbuffer(&(this->normbuffer), normals);

}

void Missile :: render_missile()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this -> Texture);
	glUniform1i(this -> TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->missile.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, this -> missile.len);

	this -> fire();
	if(this -> p_fired)
		this -> plane_fire();
	this -> missile.unbind_vertex_buffer();

}

void Missile :: fire()
{
	if(ship1.missl.s_fired)
		ship1.fire_missile(jet.plane.position);
	if(ship2.missl.s_fired)
		ship2.fire_missile(jet.plane.position);
	if(ship3.missl.s_fired)
		ship3.fire_missile(jet.plane.position);

}
void Missile :: plane_fire()
{
	if(this->missile.position.y > depth){
		this -> missile.position.y -= g;
		this -> missile.position.z += 7*g * cos(jet.y_angle);
		this -> missile.position.x += 7*g * sin(jet.y_angle);
	}
}

void Missile :: ship1_fire(vec3 pos)
{
	pos.z += 3.0;
	float x = pow((abs(ship1.ship.position.x) - abs(pos.x)), 2);
	float y = pow((abs(ship1.ship.position.y) - abs(pos.y)), 2);
	float z = pow((abs(ship1.ship.position.z) - abs(pos.z)), 2);
	float r = sqrt(x + y + z);

	this -> t = atan((pos.z - ship1.ship.position.z)/(pos.x - ship1.ship.position.x));
	float p = atan((pos.y - ship1.ship.position.y)/ sqrt(x+z));
	float t = this -> t;
	//float t = 0.5, p = 0.5;
	//float r = 0.5;
	/*p = p*(PI/180.0);
	t = t*(PI/180.0);
*/	//printf("%f\n", 180*p/PI);
	r = r/40;
	/*if(p <= 0)
		p = 0;
*/	//printf("ship missile\n");
	int i = 1;
	if(pos.x > ship1.ship.position.x)
		i = -1;
	if(this->missile.position.y < 200 || this->missile.position.y < jet.plane.position.y){
		this -> missile.position.y += r * sin(abs(p));
		this -> missile.position.z -= r * cos(p) * sin(t) * i;
		this -> missile.position.x -= r * cos(p) * cos(t) * i;
	}
	else
		this -> s_fired = false;
	//printf("%f %f %f\n", this->missile.position.x, this->missile.position.y, this->missile.position.z);
}
void Missile :: ship2_fire(vec3 pos)
{
	pos.z += 3.0;
	float x = pow((abs(ship2.ship.position.x) - abs(pos.x)), 2);
	float y = pow((abs(ship2.ship.position.y) - abs(pos.y)), 2);
	float z = pow((abs(ship2.ship.position.z) - abs(pos.z)), 2);
	float r = sqrt(x + y + z);

	this -> t = atan((pos.z - ship2.ship.position.z)/(pos.x - ship2.ship.position.x));
	float p = atan((pos.y - ship2.ship.position.y)/ sqrt(x+z));
	float t = this -> t;
	//float t = 0.5, p = 0.5;
	//float r = 0.5;
	/*p = p*(PI/180.0);
	t = t*(PI/180.0);
*/	//printf("%f\n", 180*p/PI);
	r = r/40;
	/*if(p <= 0)
		p = 0;
*/	//printf("ship missile\n");
	int i = 1;
	if(pos.x > ship2.ship.position.x)
		i = -1;
	if(this->missile.position.y < 200 || this->missile.position.y < jet.plane.position.y){
		this -> missile.position.y += r * sin(abs(p));
		this -> missile.position.z -= r * cos(p) * sin(t) * i;
		this -> missile.position.x -= r * cos(p) * cos(t) * i;
	}
	else{
		this -> s_fired = false;
		this -> missile.position = ship2.ship.position;
	}
	//printf("%f %f %f\n", this->missile.position.x, this->missile.position.y, this->missile.position.z);
}
void Missile :: ship3_fire(vec3 pos)
{
	pos.z += 3.0;
	float x = pow((abs(ship3.ship.position.x) - abs(pos.x)), 2);
	float y = pow((abs(ship3.ship.position.y) - abs(pos.y)), 2);
	float z = pow((abs(ship3.ship.position.z) - abs(pos.z)), 2);
	float r = sqrt(x + y + z);

	this -> t = atan((pos.z - ship3.ship.position.z)/(pos.x - ship3.ship.position.x));
	float p = atan((pos.y - ship3.ship.position.y)/ sqrt(x+z));
	float t = this -> t;
	//float t = 0.5, p = 0.5;
	//float r = 0.5;
	/*p = p*(PI/180.0);
	t = t*(PI/180.0);
*/	//printf("%f\n", 180*p/PI);
	r = r/40;
	/*if(p <= 0)
		p = 0;
*/	//printf("ship missile\n");
	int i = 1;
	if(pos.x > ship3.ship.position.x)
		i = -1;
	if(this->missile.position.y < 200 || this->missile.position.y < jet.plane.position.y){
		this -> missile.position.y += r * sin(abs(p));
		this -> missile.position.z -= r * cos(p) * sin(t) * i;
		this -> missile.position.x -= r * cos(p) * cos(t) * i;
	}
	else{
		this -> s_fired = false;
		this -> missile.position = ship3.ship.position;
	}
	//printf("%f %f %f\n", this->missile.position.x, this->missile.position.y, this->missile.position.z);
}