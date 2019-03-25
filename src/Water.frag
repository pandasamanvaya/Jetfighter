#version 330 core

// Ouput data
out vec3 color;

in vec3 Color;

//uniform sampler2D mySamplerTexture;

void main()
{

	//Output color = red 
	//color = texture(mySamplerTexture, texture0);
	color = Color;
}