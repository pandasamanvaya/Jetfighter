#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <lib/shader.hpp>
#include <lib/text2D.hpp>
#include <lib/objloader.hpp>
#include <lib/texture.hpp>
#include <lib/vboindexer.hpp>

#include "color.h"

using namespace glm;
using namespace std;

#define PI 3.1415926
#define EXIT_LINE 1
#define EXIT_BEAM 2
#define EXIT_BOOM 3
struct color_t {
    int r;
    int g;
    int b;
};

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float length;
    float width;
    float height;
};

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();

#endif
