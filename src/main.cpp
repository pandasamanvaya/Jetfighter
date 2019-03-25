#include "main.h"
#include "plane.h"
#include "level.h"
#include "water.h"
#include "callback.h"
#include "island.h"
#include "ship.h"
#include "scoreboard.h"
#include "timer.h"
#include "weapons.h"
#include "collision.h"

#define N 30

extern float f_len, h_len;
float depth = -100;
GLFWwindow* window;
Plane jet = Plane(0.0, 0.0, 0.0);
Ship ship1 = Ship(200, depth-5, 700);
Ship ship2 = Ship(1800, depth-5, 200);
Ship ship3 = Ship(-1500, depth-5, -200);
Water Sea = Water(0.0, 0.0, 0.0);
vec3 init_cam = vec3(0.0, 7.0, -20.0);
vec3 look_point = vec3(0.0, 0.0, 0.0);
vec3 upward = vec3(0.0, 1.0, 0.0);
vec3 eye = init_cam;
vec3 lightPos = vec3(0.0, 10.0, 0.0);
Island island[N];
Fuel fuel[N/10];
Ring ring[N];
Coin coin[N];
bool up = false, heli_view = false;
Timer tfire(5.0);
Timer t120(1/120.0);

double FoV = 45.0f;
int height = 768, width = 1366, score;


void ship_collision()
{
	if(ship_missile_col(ship1, jet.missl)){
		ship1.destroyed();
		jet.missl.missile.position.y = depth-100;
		jet.missl.p_fired = false;
		score += 50;
	}
	if(ship_missile_col(ship2, jet.missl)){
		ship2.destroyed();
		jet.missl.missile.position.y = depth-100;
		jet.missl.p_fired = false;
		score += 50;
	}
	if(ship_missile_col(ship3, jet.missl)){
		ship3.destroyed();
		jet.missl.missile.position.y = depth-100;
		jet.missl.p_fired = false;
		score += 50;
	}

	if(ship_bomb_col(ship1, jet.bmb)){
		ship1.destroyed();
		jet.bmb.bomb.position.y = depth-100;
		jet.bmb.fired = false;
		score += 100;
	}
	if(ship_bomb_col(ship2, jet.bmb)){
		ship2.destroyed();
		jet.bmb.bomb.position.y = depth-100;
		jet.bmb.fired = false;
		score += 100;
	}
	if(ship_bomb_col(ship3, jet.bmb)){
		ship3.destroyed();
		jet.bmb.bomb.position.y = depth-100;
		jet.bmb.fired = false;
		score += 100;
	}
}

void plane_collision()
{
	if(plane_missile_col(jet, ship1.missl)){
		printf("Plane hit by missile1\n");
		ship1.missl.missile.position = ship1.ship.position;
		ship1.missl.s_fired = false;
		h_len -= 0.03;
	}
	if(plane_missile_col(jet, ship2.missl)){
		printf("Plane hit by missile2\n");
		ship2.missl.missile.position = ship2.ship.position;
		ship2.missl.s_fired = false;
		h_len -= 0.03;
	}
	if(plane_missile_col(jet, ship3.missl)){
		printf("Plane hit by missile3\n");
		ship3.missl.missile.position = ship3.ship.position;
		ship3.missl.s_fired = false;
		h_len -= 0.03;
	}

	for(int i = 0; i < N; i++){
		if(plane_volcano_col(jet, island[i])){
			game_over();
			printf("Volcano region\n");
		}
	}
	for(int i = 0; i < N/10; i++){
		if(plane_fuel_col(jet, fuel[i])){
			f_len = 0.5;
			score += 10;
			fuel[i].fuel.position.y = 2*depth;
		}
	}
	
	for(int i = 0; i < N; i++){
		if(plane_ring_col(jet, ring[i])){
			score += 100;		
			ring[i].ring.position.y = 2*depth;
		}
	}

	for(int i = 0; i < N; i++){
		if(plane_coin_col(jet, coin[i])){
			score += 100;		
			coin[i].coin.position.y = 2*depth;
		}
	}

	if(h_len <= 0 || f_len <= 0 || jet.plane.position.y <= depth)
		game_over();
}

void check_collision()
{
	ship_collision();
	plane_collision();
}

void fire_missiles()
{
	if(!ship1.dead)
		ship1.missl.s_fired = true;
	else if(!ship2.dead)
		ship2.missl.s_fired = true;
	else if(!ship3.dead)
		ship3.missl.s_fired = true;
	else
		won_game(score);
}

void create_random()
{
	for(int i = 0; i < N; i++)
		island[i].create_island();
	
	for(int i = 0; i < N/10; i++)
		fuel[i].create_fuel();
	
	for(int i = 0; i < N; i++)
		ring[i].create_ring();

	for(int i = 0; i < N; i++)
		coin[i].create_coin();
}

void render_random(GLuint Projection, mat4 MVP2)
{
	for(int i = 0; i < N; i++)
		island[i].render_island(Projection, MVP2);

	for(int i = 0; i < N/10; i++){
		fuel[i].MVP = MVP2;
		fuel[i].render_fuel(Projection);
	}
	for(int i = 0; i < N; i++){
		ring[i].MVP = MVP2;
		ring[i].render_ring(Projection);
	}
	for(int i = 0; i < N; i++){
		coin[i].MVP = MVP2;
		coin[i].render_coin(Projection);
	}
}

void create_objects(GLuint objShader)
{
	//Plane
	jet.create_plane("../lib/plane.bmp", "../lib/plane.obj", objShader);
	jet.missl.create_missile("../lib/plane.bmp", "../lib/missile.obj", objShader);
	jet.bmb.create_bomb("../lib/plane.bmp", "../lib/bomb.obj", objShader);
	
	//Ship
	ship1.create_ship("../lib/ship.bmp", "../lib/ship.obj", objShader);
	ship2.create_ship("../lib/ship.bmp", "../lib/ship.obj", objShader);
	ship3.create_ship("../lib/ship.bmp", "../lib/ship.obj", objShader);
	ship1.missl.create_missile("../lib/plane.bmp", "../lib/missile.obj", objShader);
	ship2.missl.create_missile("../lib/plane.bmp", "../lib/missile.obj", objShader);
	ship3.missl.create_missile("../lib/plane.bmp", "../lib/missile.obj", objShader);
	ship1.arrow.create_arrow();
	ship2.arrow.create_arrow();
	ship3.arrow.create_arrow();
	
	Sea.create_water();
	create_random();
}

int main()
{
	window = create_window(height, width);
	if(window == NULL){
		printf("Window not created\n");
		exit(3);
	}	
	
	GLuint vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
	
	//Shader for Plane
	GLuint objShader = LoadShaders( "../src/Plane.vert", "../src/Plane.frag" );
	GLuint MatrixID = glGetUniformLocation(objShader, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(objShader, "V");
	GLuint ModelMatrixID = glGetUniformLocation(objShader, "M");
	glUseProgram(objShader);
	GLuint LightID = glGetUniformLocation(objShader, "LightPosition_worldspace");
	
	//Shader for enviroment objects
	GLuint EnvShader = LoadShaders( "../src/Water.vert", "../src/Water.frag" );
	GLuint Projection = glGetUniformLocation(EnvShader, "Projection");

	create_objects(objShader);

	initText2D( "../lib/Holstein.DDS" );
	
	mat4 Model = mat4(1.0f);

	do{
		mat4 Project = perspective(radians(FoV), 16.0/9.0, 0.1, 2000.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao1);

		if(t120.processTick()){
			if(glfwSetKeyCallback(window, key_callback) and !up)
				jet.fall();
			if(glfwSetKeyCallback(window, key_callback) and heli_view){
				move_mouse(window);
				glfwSetScrollCallback(window, scroll_callback);
			}
			glfwSetMouseButtonCallback(window, mouse_callback);
			
			check_collision();
			print_score(EnvShader, Projection);
			//printf("%f\n", look_point.x);
			mat4 View = lookAt(eye+jet.plane.position, look_point+jet.plane.position, upward);
			mat4 Translate = translate(mat4(1.0), jet.plane.position);
			mat4 Rotater = rotate(mat4(1.0f), jet.r_angle, vec3(0.0, 0.0, 1.0));
			mat4 Rotatey = rotate(mat4(1.0f), jet.y_angle, vec3(0.0, 1.0, 0.0));
			mat4 Rotate = Rotatey * Rotater;
			mat4 MVP = mat4(1.0f) * Project * View * Translate * Rotate;
			mat4 MVP2 = mat4(1.0f) * Project * View;

			//Rendering Plane
			glUseProgram(objShader);
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			jet.render_plane(Projection, MVP);
			//glUseProgram(0);
			//glUseProgram(objShader);
			Rotate = rotate(mat4(1.0f), jet.y_angle, vec3(0.0, 1.0, 0.0));
			Translate = translate(mat4(1.0), jet.missl.missile.position);
			mat4 MVP1 = Project * View * Translate * Rotate;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			jet.missl.render_missile();
			
			Translate = translate(mat4(1.0), jet.bmb.bomb.position);
			MVP1 = Project * View * Translate * Rotate;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			jet.bmb.render_bomb();

			//Rendering Ship
			Translate = translate(mat4(1.0), ship1.ship.position);
			MVP1 = Project * View * Translate;
			//ship1.MVP = MVP1;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			ship1.render_ship(Projection);
			//ship_collision(ship1);
			glUseProgram(0);
			ship1.arrow.MVP = MVP1;
			
			glUseProgram(objShader);
			
			Translate = translate(mat4(1.0), ship1.missl.missile.position);
			Rotate = rotate(mat4(1.0), radians(180.0f), vec3(0.0, 1.0, 0.0));
			MVP1 = Project * View * Translate * Rotate;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			ship1.missl.render_missile();
			/*if(tfire.processTick() && !(ship1.dead))
				ship1.missl.s_fired = true;*/
			Translate = translate(mat4(1.0), ship2.ship.position);
			MVP1 = Project * View * Translate;
			//ship2.arrow.MVP = MVP1;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			ship2.render_ship(Projection);
			//ship_collision(ship2);

			ship2.arrow.MVP = MVP1;

			Translate = translate(mat4(1.0), ship2.missl.missile.position);
			Rotate = rotate(mat4(1.0), radians(-90.0f), vec3(0.0, 1.0, 0.0));
			MVP1 = Project * View * Translate * Rotate;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			ship2.missl.render_missile();
			/*if(tfire.processTick() && !(ship2.dead))
				ship2.missl.s_fired = true;
*/
			Translate = translate(mat4(1.0), ship3.ship.position);
			MVP1 = Project * View * Translate;
			//ship3.MVP = MVP1;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			ship3.render_ship(Projection);
			//ship_collision(ship3);
			ship3.arrow.MVP = MVP1;

			Translate = translate(mat4(1.0), ship3.missl.missile.position);
			Rotate = rotate(mat4(1.0), radians(-90.0f), vec3(0.0, 1.0, 0.0));
			MVP1 = Project * View * Translate * Rotate;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
			ship3.missl.render_missile();
			/*if(tfire.processTick() && !(ship3.dead))
				ship3.missl.s_fired = true;
*/			
			glUseProgram(0);
			
			//Rendering Sea
			glUseProgram(EnvShader);
			Sea.render_water(Projection, MVP2);
			
			//Rendering Random elements
			render_random(Projection, MVP2);

			ship1.arrow.render_arrow(Projection);
			ship2.arrow.render_arrow(Projection);
			ship3.arrow.render_arrow(Projection);
			
			if(tfire.processTick())
				fire_missiles();
			/*jet.arrow.MVP = MVP;
			jet.arrow.MVP = translate(jet.arrow.MVP, vec3(0.0, 3, -50.0));
			jet.arrow.MVP = rotate(jet.arrow.MVP, radians(90.0f), vec3(1.0, 0.0, 0.0));
			jet.arrow.render_arrow(Projection);
*/
			glUseProgram(0);
			glBindVertexArray(0);
			glfwSwapBuffers(window);
		}

		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	/*glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
*/	jet.plane.unbind_buffer(jet.plane.vertexbuffer, jet.uvbuffer, jet.normbuffer);
	glDeleteProgram(objShader);
	//glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &vao1);

	// Close OpenGL window and terminate GLFW
	game_over();

	return 0;
}