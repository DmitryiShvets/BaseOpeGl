#version 330 core
layout (location = 0) in vec2 position;// Устанавливаем позицию атрибута в 0

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelMatrix *vec4(position, 0.0, 1.0);// Напрямую передаем vec3 в vec4
}