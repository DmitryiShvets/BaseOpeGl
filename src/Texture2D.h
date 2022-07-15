//
// Created by Dmitry on 13.06.2022.
//

#ifndef BASEOPEGL_TEXTURE2D_H
#define BASEOPEGL_TEXTURE2D_H

#include <GL/glew.h>
#include <string>

#include "SubTexture2D.h"

class Texture2D {
public:

    Texture2D(const char *path);

    ~Texture2D();

    Texture2D() = delete;

    Texture2D(Texture2D &) = delete;

    Texture2D &operator=(const Texture2D &) = delete;

    Texture2D &operator=(Texture2D &&texture2D) noexcept;

    Texture2D(Texture2D &&texture2D) noexcept;

    void bind();

    int width();

    int height();

    virtual const SubTexture2D &getSubTexture(const size_t &subTexName);

public:
    int mWidth = 0;
    int mHeight = 0;
    int channel = 0;
    GLenum format;
    GLuint textureID = 0;


};


#endif //BASEOPEGL_TEXTURE2D_H
