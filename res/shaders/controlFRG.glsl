#version 330 core

uniform vec3 color;

out vec4 Color;

void main()
{
    Color =  vec4(color, 1.0);
}