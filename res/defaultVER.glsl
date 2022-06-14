#version 330 core
layout (location = 0) in vec3 position;// Устанавливаем позицию атрибута в 0
layout (location = 1) in vec3 col;// Устанавливаем позицию атрибута в 0
layout (location = 2) in vec2 texCoord;

out vec4 vertexColor;// Передаем цвет во фрагментный шейдер
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0);// Напрямую передаем vec3 в vec4
    vertexColor = vec4(col, 1.0f);// Устанавливаем значение выходной переменной в темно-красный цвет.
    TexCoord = texCoord;
}