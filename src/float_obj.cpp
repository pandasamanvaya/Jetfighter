#include "float_obj.h"

extern float depth;
extern float f_len;

//Checkpoint Arrow
float len = 30.0;
Arrow :: Arrow()
{
	this -> arrow.position = vec3(0.0, 100.0, 0.0);
	int off = 0;
	float p1[] = {len, 0.0, 0.0};
	float p2[] = {-len, 0.0, 0.0};
	float p3[] = {0.0, -len, 0.0};
	create_triangle(this->arrow.vertdata, 0, p1, p2, p3);
	this->arrow.len = 9;
	off = this->arrow.len;
	shift_shape(this->arrow.vertdata, 0, off, 0.0, -2*len, 0);

	this->arrow.len += drawRectangle(this->arrow.vertdata, off, len, 2*len);
	shift_shape(this->arrow.vertdata, off, this->arrow.len, -len/2, -2*len, 0);
	
	shift_shape(this->arrow.vertdata, 0, this->arrow.len, 0, 70, 0);
	color_shape(this->arrow.texcord, 0, this->arrow.len, red);
}

void Arrow :: create_arrow()
{
	glGenBuffers(1, &(this->arrow.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->arrow.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->arrow.vertdata), this->arrow.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->arrow.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->arrow.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->arrow.texcord), this->arrow.texcord, GL_STATIC_DRAW);

}

void Arrow :: render_arrow(GLuint Projection)
{
	mat4 transform = translate(this->MVP, this->arrow.position);
	transform = rotate(transform, radians(20.0f), vec3(0.0, 1.0, 0.0));
	//this -> MVP = this -> MVP * Rotate;
	//printf("%f\n", this -> MVP[0][0]);
	
	glUniformMatrix4fv(Projection, 1, GL_FALSE, &(transform[0][0]));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->arrow.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->arrow.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> arrow.len)/3);
	//printf("Arrow\n");
	//this -> arrow.unbind_vertex_buffer();
	if(move)
		this -> move_arrow();
}

void Arrow :: move_arrow()
{
	float speed = 2.0;
	static int i = 0, dur = 150;
	if(this -> arrow.position.y < 150 and i < dur/2){
		this -> arrow.position.y += speed;
		i++;
	}
	else if(this -> arrow.position.y > 0 and i < dur){
		this -> arrow.position.y -= speed;
		i++;
	}
	else i = 0;
}

void Arrow :: disappear()
{
	this -> arrow.position.y = depth-2*len;
	this -> move = false;
}

//Fuelup
Fuel :: Fuel()
{
	static unsigned int i = 1;
	srand(i++);
	float x = (rand() % 2000) - 1000;
	float y = (rand() % 50) - 100;
	float z = (rand() % 2000) - 1000;

	this -> fuel.position = vec3(x, y, z);
	//printf("%f %f %f\n", this->fuel.position.x, this->fuel.position.y, this->fuel.position.z);

	this -> fuel.len = create_cuboid(this->fuel.vertdata, 0, 2, 5, 5);
	color_shape(this->fuel.texcord, 0, this->fuel.len, yellow);
}

void Fuel :: create_fuel()
{
	glGenBuffers(1, &(this->fuel.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->fuel.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->fuel.vertdata), this->fuel.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->fuel.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->fuel.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->fuel.texcord), this->fuel.texcord, GL_STATIC_DRAW);

}

void Fuel :: render_fuel(GLuint Projection)
{
	mat4 transform = translate(this->MVP, this->fuel.position);
	
	static float i = 0;
	if(i > 360)
		i = 0;
	transform = rotate(transform, radians(i++), vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(Projection, 1, GL_FALSE, &(transform[0][0]));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->fuel.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->fuel.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> fuel.len)/3);
}

Ring :: Ring()
{
	static unsigned int i = 1;
	srand(i++);
	float x = (rand() % 2000) - 1000;
	float y = (rand() % 20) - 10;
	float z = (rand() % 2000) - 1000;

	this -> ring.position = vec3(x, y, z);
	this -> ring.len = draw_ring(this->ring.vertdata, 0, 5.0, 0.3, 0.5);
	color_shape(this->ring.texcord, 0, this->ring.len, green);

}

void Ring :: create_ring()
{
	glGenBuffers(1, &(this->ring.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->ring.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->ring.vertdata), this->ring.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->ring.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->ring.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->ring.texcord), this->ring.texcord, GL_STATIC_DRAW);

}

void Ring :: render_ring(GLuint Projection)
{
	MVP = translate(MVP, this -> ring.position);

	glUniformMatrix4fv(Projection, 1, GL_FALSE, &(MVP[0][0]));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->ring.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->ring.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> ring.len)/3);

}

Coin :: Coin()
{
	static unsigned int i = 10;
	srand(i++);
	float x = (rand() % 1500) - 1000;
	float y = (rand() % 30) - 10;
	float z = (rand() % 2500) - 700;

	this -> coin.position = vec3(x, y, z);
	this -> coin.len = create_regular_poly(this->coin.vertdata, 0, 20, 2);
	color_shape(this->coin.texcord, 0, this->coin.len, yellow);

}

void Coin :: create_coin()
{
	glGenBuffers(1, &(this->coin.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->coin.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coin.vertdata), this->coin.vertdata, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->coin.texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->coin.texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coin.texcord), this->coin.texcord, GL_STATIC_DRAW);

}

void Coin :: render_coin(GLuint Projection)
{
	MVP = translate(MVP, this -> coin.position);

	glUniformMatrix4fv(Projection, 1, GL_FALSE, &(MVP[0][0]));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->coin.vertexbuffer);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->coin.texbuffer);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, (this -> coin.len)/3);

}