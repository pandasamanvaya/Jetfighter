#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"

#define MAX 100000

class Object{
public:
	GLuint vertexbuffer;
	GLuint texbuffer;
	GLfloat vertdata[MAX];
	GLfloat texcord[MAX];	
	int len = 0;
	vec3 position = vec3(0.0, 0.0, 0.0);

	void bind_vertbuffer(GLuint*, vector<vec3>);
	void bind_uvbuffer(GLuint*, vector<vec2>);
	void bind_normbuffer(GLuint*, vector<vec3>);

	void unbind_buffer(GLuint, GLuint, GLuint);
	void unbind_buffer(GLuint, GLuint);
	void unbind_vertex_buffer();

};

#endif