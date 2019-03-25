#include "ship.h"

Ship :: Ship(float x, float y, float z)
{
	this -> ship.position = vec3(x, y, z);
	this -> missl.missile.position = this -> ship.position;
}

void Ship :: create_ship(const char *texfile, const char *objfile, GLuint programID)
{
	this -> Texture = loadBMP_custom(texfile);
	this -> TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals; 

	bool res = loadOBJ(objfile, vertices, uvs, normals);

	this -> ship.len = vertices.size();
	this -> bindbuffer(vertices, uvs, normals);
}

void Ship :: bindbuffer(vector<vec3>vertices, vector<vec2>uvs, vector<vec3>normals)
{
	ship.bind_vertbuffer(&(this->ship.vertexbuffer), vertices);
	ship.bind_uvbuffer(&(this->uvbuffer), uvs);
	ship.bind_normbuffer(&(this->normbuffer), normals);
}

void Ship :: bindTexture()
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this -> Texture);
	glUniform1i(this -> TextureID, 0);

}

void Ship :: render_ship(GLuint Projection)
{
	this -> bindTexture();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->ship.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, this -> ship.len);
	glBindTexture(GL_TEXTURE_2D, 0);
	

	this -> ship.unbind_vertex_buffer();
}

void Ship :: destroyed()
{	
	this -> Texture = loadBMP_custom("../lib/dead.bmp");
	this -> arrow.disappear();
	this -> missl.s_fired = false;
	this -> dead = true;
}

void Ship :: fire_missile(vec3 pos)
{
	pos.z += 1.0;
	float x = pow((abs(this->ship.position.x) - abs(pos.x)), 2);
	float y = pow((abs(this->ship.position.y) - abs(pos.y)), 2);
	float z = pow((abs(this->ship.position.z) - abs(pos.z)), 2);
	float r = sqrt(x + y + z);

	float t = atan((pos.z - this->ship.position.z)/(pos.x - this->ship.position.x));
	float p = atan((pos.y - this->ship.position.y)/ sqrt(x+z));
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
	if(pos.x > this->ship.position.x)
		i = -1;
	if(this->missl.missile.position.y < 200 || this->missl.missile.position.y < pos.y){
		this -> missl.missile.position.y += r * sin(abs(p));
		this -> missl.missile.position.z -= r * cos(p) * sin(t) * i;
		this -> missl.missile.position.x -= r * cos(p) * cos(t) * i;
	}
	else{
		this -> missl.s_fired = false;
		this -> missl.missile.position = this -> ship.position;
	}
	//printf("%f %f %f\n", this->missl.missile.position.x, this->missl.missile.position.y, this->missl.missile.position.z);

}