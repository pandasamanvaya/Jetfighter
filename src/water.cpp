#include "water.h"

extern float depth;

Water :: Water(float x, float y, float z)
{
	this -> sea.position = vec3(x, y, z);

	float size = 73000;
/*	float p1[] = {size/2, depth, size/2};
	float p2[] = {-size/2, depth, -size/2};
	float p3[] = {-size/2, depth, size/2};
	float p4[] = {size/2, depth, -size/2};

	create_triangle(this -> sea.vertdata, 0, p1, p2, p3);
	create_triangle(this -> sea.vertdata, 9, p1, p2, p4);*/
	//create_triangle(this -> sea.vertdata, 18, p1, p2, p5);
	this->sea.len = create_regular_poly(this->sea.vertdata, 0, 4, size/2.0, depth);
	/*shift_shape(this->sea.vertdata, 0, this->sea.len, 0, 100);
	int off = this->sea.len;
	this->sea.len = create_regular_poly(this->sea.vertdata, off, 4, 200, depth);
	shift_shape(this->sea.vertdata, off, this->sea.len, 0, 100);
*/	color_shape(this->sea.texcord, 0, this->sea.len, blue);
	//printf("%f\n", sea.texcord[17]);
}

void Water :: create_water()
{

	glGenBuffers(1, &(this->sea.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->sea.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->sea.vertdata), this->sea.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->sea.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->sea.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->sea.texcord), this->sea.texcord, GL_STATIC_DRAW);

}

void Water :: render_water(GLuint Projection, mat4 MVP)
{
	/*mat4 rot = rotate(mat4(1.0f), float(radians(45.0)), vec3(0.0, 1.0, 0.0));

	MVP = MVP * rot;
*/	glUniformMatrix4fv(Projection, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->sea.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->sea.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> sea.len)/3);

	this -> sea.unbind_vertex_buffer();
}

