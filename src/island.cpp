#include "island.h"

extern float depth;

Island :: Island()
{	
	static unsigned int i = 1;
	srand(i++);
	float r = 50.0;
	float x = (rand() % 5000) - 1000;
	float z = (rand() % 5000) - 1000;

//	printf("%f %f\n",x, z);
	this -> isld.position = vec3(x, depth, z);

	this -> isld.len = create_regular_poly(this->isld.vertdata, 0, 15, r, depth+2);
	shift_shape(this->isld.vertdata, 0, this->isld.len, x, 0, z);

	int off = this->isld.len;
	this -> isld.len = create_frustum(this->isld.vertdata, off, 2, r-20, 20);
	shift_shape(this->isld.vertdata, off, this->isld.len, x, depth+2, z);
	
	color_shape(this->isld.texcord, 0, off, green);
	color_shape(this->isld.texcord, off, this -> isld.len, brown);
	
	off = this->isld.len;
	this -> isld.len = create_regular_poly(this->isld.vertdata, off, 20, 9, depth+22);
	shift_shape(this->isld.vertdata, off, this->isld.len, x, 0, z);
	color_shape(this->isld.texcord, off, this -> isld.len, red);

}

void Island :: create_island()
{
	glGenBuffers(1, &(this->isld.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->isld.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->isld.vertdata), this->isld.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->isld.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->isld.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->isld.texcord), this->isld.texcord, GL_STATIC_DRAW);

}

void Island :: render_island(GLuint Projection, mat4 MVP)
{
	/*mat4 Translate = translate(mat4(1.0f), vec3(0.0, -95.0, 0.0));
	MVP *= Translate;*/
	glUniformMatrix4fv(Projection, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->isld.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->isld.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> isld.len)/3);

	this -> isld.unbind_vertex_buffer();
}