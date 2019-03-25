#include "level.h"

GLFWwindow* create_window(int height, int width)
{
	if(!glfwInit()){
		fprintf(stderr, "Unable to initialize glfw\n");
		exit(GLFW_FAIL);
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Jetfighter", NULL, NULL);

	if(window == NULL){
		printf("Window not created\n");
		exit(3);
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(GLEW_FAIL);
	}

	glEnable(GL_COLOR_MATERIAL | GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glfwPollEvents();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glClearColor(0.0, 155.0/256, 255.0/256, 0.0);
	//glEnable(GL_CULL_FACE);
	return window;
}

void game_over()
{
	printf("Game Over\n");
	glfwTerminate();
	exit(0);
}

void won_game(int score)
{
	printf("You Won\nYour Score = %d\n", score);
	glfwTerminate();
	exit(0);

}