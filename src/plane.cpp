#include "plane.h"

Aim :: Aim()
{
	this -> aim.len = draw_ring(this -> aim.vertdata, 0, 1, 0.3, 1.0);
	shift_shape(this->aim.vertdata, 0, this->aim.len, 0.0, -5.0, 60);
	color_shape(this->aim.texcord, 0, this->aim.len, green);
}

void Aim :: create_aim()
{
	glGenBuffers(1, &(this->aim.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->aim.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->aim.vertdata), this->aim.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->aim.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->aim.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->aim.texcord), this->aim.texcord, GL_STATIC_DRAW);

}

void Aim:: render_aim(GLuint Projection, mat4 MVP)
{
	glUniformMatrix4fv(Projection, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->aim.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->aim.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> aim.len)/3);

	this -> aim.unbind_vertex_buffer();

}

Plane :: Plane(float x, float y, float z)
{
	this -> plane.position = vec3(x, y, z);
}

void Plane :: create_plane(const char *texfile, const char *objfile, GLuint programID)
{
	this -> Texture = loadBMP_custom(texfile);
	this -> TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals; 

	bool res = loadOBJ(objfile, vertices, uvs, normals);
	this -> plane.len = vertices.size();
	this -> bindbuffer(vertices, uvs, normals);
	this -> create_aim();
}

void Plane :: bindbuffer(vector<vec3>vertices, vector<vec2>uvs, vector<vec3>normals)
{
	plane.bind_vertbuffer(&(this->plane.vertexbuffer), vertices);
	plane.bind_uvbuffer(&(this->uvbuffer), uvs);
	plane.bind_normbuffer(&(this->normbuffer), normals);
}

void Plane :: bindTexture()
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this -> Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(this -> TextureID, 0);

}

void Plane :: render_plane(GLuint Projection, mat4 MVP)
{
	this -> bindTexture();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->plane.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, this -> plane.len);
	this -> move_plane();
	this -> plane.unbind_vertex_buffer();

	float z = cos(this -> y_angle) * 50;
	this -> aim.position = vec3(this->plane.position.x, depth + 5, this->plane.position.z+z);
	this -> render_aim(Projection, MVP);
}

void Plane :: move_plane()
{
	this -> speed_z = cos(this -> y_angle) * fact;
	this -> speed_x = sin(this -> y_angle) * fact;
	this -> plane.position.z += speed_z;
	this -> plane.position.x += speed_x;
}

void Plane :: moveup()
{
	this -> plane.position.y += 0.2;
}

void Plane :: fall()
{
	if(this -> plane.position.y > depth){
		this -> plane.position.y -= 0.1;
	}
}

/*void Plane :: fire_bomb()
{
	bmb.fired = true;
}
*/
extern float g;

void Plane :: fire_missile()
{
	if(this->missl.missile.position.y > depth){
		this -> missl.missile.position.y -= g;
		this -> missl.missile.position.z += 7*g * cos(this->y_angle);
		this -> missl.missile.position.x += 7*g * sin(this->y_angle);
	}
}