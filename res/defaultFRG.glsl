#version 330 core

in vec4 vertexColor;
out vec4 color;

//uniform vec4 ourColor;// Мы устанавливаем значение этой переменной в коде OpenGL.

void main()
{
    color = vertexColor;
}