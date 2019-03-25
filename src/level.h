#ifndef LEVEL_H
#define LEVEL_H

#include "main.h"

#define GLFW_FAIL 1
#define GLEW_FAIL 2

GLFWwindow* create_window(int, int);
void game_over();
void won_game(int);

#endif