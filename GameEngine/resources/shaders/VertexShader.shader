#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexColor;

out vec3 fragColor;

void main()
{
	gl_Position = position;
	fragColor = vertexColor;
}