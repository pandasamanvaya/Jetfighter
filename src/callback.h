#include "main.h"
#include "plane.h"
#include "ship.h"
#include "weapons.h"
#include "collision.h"

extern vec3 eye, init_cam, look_point, upward;
extern Plane jet;
extern bool up, heli_view;
extern int height, width;
extern double FoV;
extern Ship ship1,ship2, ship3;
bool view = false;

void move_mouse(GLFWwindow* window)
{
	double xpos, ypos;
	float horizontalAngle = 0.0f, verticalAngle = 0.0f;
	float speed = 3.0f, mouseSpeed = 0.005f;
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	glfwGetCursorPos(window, &xpos, &ypos);

	horizontalAngle += mouseSpeed * float(width/2 - xpos );
	verticalAngle   += mouseSpeed * float(height/2 - ypos );

	vec3 direction = vec3(
		30 * sin(horizontalAngle) * cos(verticalAngle), 
		30 * sin(verticalAngle),
		30 * cos(horizontalAngle) * cos(verticalAngle)
	);
	
	vec3 right = glm::vec3(
		-cos(horizontalAngle), 
		0,
		sin(horizontalAngle)
	);
	vec3 up = cross( right, direction );
	
	//printf("%f\n", direction.x);
	look_point = direction;
	upward = up;
	lastTime = currentTime;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float tilt = 0.25, p = 20.0;

	if(key == GLFW_KEY_Q){
		jet.r_angle -= 0.01;
		jet.y_angle += 0.01;
		//anglew += 0.01;
		if(jet.r_angle <= -tilt){
			jet.r_angle = -tilt;
		}
		if(action == GLFW_RELEASE){
			jet.r_angle = 0.0;
		}
	}
	else if(key == GLFW_KEY_E){
		jet.y_angle -= 0.01;
		jet.r_angle += 0.01;
		if(jet.r_angle >= tilt){
			jet.r_angle = tilt;
		}
		if(action == GLFW_RELEASE){
			jet.r_angle = 0.0;
		}
	}

	else if(key == GLFW_KEY_A){
		jet.r_angle -= 0.01;
	}
	else if(key == GLFW_KEY_D){
		jet.r_angle += 0.01;
	}
	else if(key == GLFW_KEY_SPACE){
		jet.moveup();
		up = true;
		if(action == GLFW_RELEASE)
			up = false;
	}
	else if(key == GLFW_KEY_W){
		/*jet.speed_x += 0.1;
		jet.speed_z += 0.1;*/
		if(jet.fact < 1.6)
			jet.fact += 0.01;
		if(action == GLFW_RELEASE){
			/*jet.speed_x -= 0.1;
			jet.speed_z -= 0.1;*/
			jet.fact = 0.3;
		}
	}
	
	float a_s = sin(jet.y_angle);
	float a_c = cos(jet.y_angle);

	if(key == GLFW_KEY_T){
		eye = vec3(0.0, 150, -1.0);
		heli_view = false;
	}
	else if(key == GLFW_KEY_F){
		eye = init_cam;
		look_point = vec3(0.0, 0.0, 0.0);
		view = false;
		heli_view = false;
	}
	else if(key == GLFW_KEY_P){
		eye = vec3(0.0, 4.0, 0.0);
		look_point = vec3(0.0, 0.0, 25.0);
		heli_view = false;
		view = true;
	}
	else if(key == GLFW_KEY_L){
		eye = vec3(100.0, 10.0, 10.0);
		heli_view = false;
		view = true;
	}
	else if(key == GLFW_KEY_H){
		heli_view = true;
		glfwSetCursorPos(window, width/2, height/2);

	}
	
	if(!heli_view){
		glfwSetCursorPos(window, width/2, height/2);
		upward = vec3(0.0, 1.0, 0.0);
		FoV = 45.0;
	}

	if(!view){
		eye.x = -20*a_s;
		eye.z = -20*a_c;
	}	
	else{
		look_point.x = 20*a_s;
		look_point.z = 20*a_c;
	}

}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS){
		jet.missl.missile.position = jet.plane.position;
		jet.missl.missile.position.z = jet.plane.position.z + 7.0 * cos(jet.y_angle);
		jet.missl.missile.position.x = jet.plane.position.x + 7.0 * sin(jet.y_angle);
		//jet.fire_missile();
		jet.missl.p_fired = true;
		//ship1.missl.missile.position = ship1.ship.position;
		//ship1.missl.s_fired = true;
		//ship2.missl.s_fired = true;
		//ship2.fire_missile(jet.plane.position);
		//ship3.missl.s_fired = true;
		//ship3.fire_missile(jet.plane.position);
		printf("Left\n");
		
	}

	if(button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_PRESS){
		printf("Right\n");
		jet.bmb.bomb.position = jet.plane.position;
		jet.bmb.fired = true;
		//ship1.missl.missile.position = ship1.ship.position;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	static float factor = 1.0;
	if(yoffset > 0){
		//Zoom out
		 FoV += factor;
		 if(FoV >= 90.0)
			FoV = 90.0;
	}
	else{
		//Zoom in
		FoV -= factor;
		if(FoV < 1.0)
			FoV = 1.0;
	} 
}