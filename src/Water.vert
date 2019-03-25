#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 colordata;
//layout(location = 1) in vec2 vn;

out vec3 Color;
uniform mat4 Projection;

void main(){

    gl_Position = Projection * vec4(vertexPosition_modelspace,1);
    Color = colordata;
}

