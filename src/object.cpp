#include "object.h"

void Object :: bind_vertbuffer(GLuint *vertexbuffer, vector<vec3> vertices)
{
	glGenBuffers(1, vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

void Object :: bind_uvbuffer(GLuint *uvbuffer, vector<vec2> uvs)
{
	glGenBuffers(1, uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

void Object :: bind_normbuffer(GLuint *normalbuffer, vector<vec3> normals)
{
	glGenBuffers(1, normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

}

void Object :: unbind_buffer(GLuint vertexbuffer, GLuint uvbuffer, GLuint normalbuffer)
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}

void Object :: unbind_buffer(GLuint vertexbuffer, GLuint texbuffer)
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &texbuffer);

}

void Object :: unbind_vertex_buffer()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}
