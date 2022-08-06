//
// Created by Dmitry on 17.07.2022.
//

#ifndef BASEOPEGL_RENDER_H
#define BASEOPEGL_RENDER_H

#include "BufferObjects.h"
#include "ShaderProgram.h"

class Renderer {
public:
    static void draw(const VAO &vao, const EBO &ebo);

    static void draw(const VAO &vao);

    static void draw(VAO *vao);

    static void setClearColor(float r, float g, float b, float a);

    static void clear();

    static void setViewPort(int x, int y, int width, int height);
};


#endif //BASEOPEGL_RENDER_H
