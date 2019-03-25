#include "scoreboard.h"

extern Plane jet;
extern float depth;
extern int score;

float f_len = 0.5, h_len = 0.5;
void render_fuel(GLuint EnvShader, GLuint Projection)
{
	float fuel_data[50], fuel_color[50];
	GLuint fuel_vertex, fuel_texture;

	int len = drawRectangle(fuel_data, 0, f_len, 0.1);
	shift_shape(fuel_data, 0, len, -0.85, -0.95, 0.0);
	color_shape(fuel_color, 0, len, yellow);

	glGenBuffers(1, &(fuel_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, fuel_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fuel_data), fuel_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(fuel_texture));
	glBindBuffer(GL_ARRAY_BUFFER, fuel_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fuel_color), fuel_color, GL_STATIC_DRAW);

	mat4 MVP = mat4(1.0f);
	glUseProgram(EnvShader);
	glUniformMatrix4fv(Projection, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, fuel_vertex);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, fuel_texture);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, len/3);
	glUseProgram(0);
}

void render_health(GLuint EnvShader, GLuint Projection)
{
	float life_data[50], life_color[50];
	GLuint life_vertex, life_texture;

	int len = drawRectangle(life_data, 0, h_len, 0.1);
	shift_shape(life_data, 0, len, 0.35, -0.95, 0.0);
	color_shape(life_color, 0, len, red);

	glGenBuffers(1, &(life_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, life_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(life_data), life_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(life_texture));
	glBindBuffer(GL_ARRAY_BUFFER, life_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(life_color), life_color, GL_STATIC_DRAW);

	mat4 MVP = mat4(1.0f);
	glUseProgram(EnvShader);
	glUniformMatrix4fv(Projection, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, life_vertex);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, life_texture);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, len/3);
	glUseProgram(0);
}

void render_compass(GLuint EnvShader, GLuint Projection)
{
	float comp_data[20000], comp_color[20000];
	GLuint comp_vertex, comp_texture;

	//printf("Compass\n");
	mat4 MVP = mat4(1.0f);
	int len = draw_ring(comp_data, 0, 0.2, 0.01, 0.5);
	//shift_shape(comp_data, 0, len, 0.6, -0.35, 0.0);
	color_shape(comp_color, 0, len, yellow);

	int off = len;
	len += drawRectangle(comp_data, off, 0.4, 0.01);
	shift_shape(comp_data, off, len, -0.2, 0.0, 0.0);
	color_shape(comp_color, off, len, red);
	glGenBuffers(1, &(comp_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, comp_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(comp_data), comp_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(comp_texture));
	glBindBuffer(GL_ARRAY_BUFFER, comp_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(comp_color), comp_color, GL_STATIC_DRAW);

	MVP = translate(MVP, vec3(0.7, 0.0, 0.0));
	MVP = rotate(MVP, radians(90.0f + 28.5f*jet.y_angle), vec3(0.0, 0.0, 1.0));
	glUseProgram(EnvShader);
	glUniformMatrix4fv(Projection, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, comp_vertex);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, comp_texture);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, len/3);

	glUseProgram(0);
}
void print_score(GLuint EnvShader, GLuint Projection)
{
	char Speed[50], Height[50], Score[50];
	float speed = (pow(jet.speed_x, 2)*100 + pow(jet.speed_z, 2)*100);

	sprintf(Speed, "Speed %.0f", speed+200);
	printText2D(Speed, 0, 500, 17);

	sprintf(Height, "Alt. %.0f", jet.plane.position.y - depth);
	printText2D(Height, 650, 500, 17);

	sprintf(Score, "Score %d", score);
	printText2D(Score, 350, 500, 17);

	if(f_len >= 0)
		f_len -= 0.0001;
	printText2D("Fuel", 120, 50, 17);
	render_fuel(EnvShader, Projection);
	
	printText2D("Health", 600, 50, 17);
	render_health(EnvShader, Projection);
	render_compass(EnvShader, Projection);
}