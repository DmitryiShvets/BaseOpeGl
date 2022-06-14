//
// Created by Dmitry on 13.06.2022.
//

#ifndef BASEOPEGL_TEXTURE2D_H
#define BASEOPEGL_TEXTURE2D_H

#include <GL/glew.h>



class Texture2D {
public:
    Texture2D();

    Texture2D(const char *path);

     ~Texture2D();

    Texture2D(Texture2D &) = delete;

    Texture2D &operator=(const Texture2D &) = delete;

    Texture2D &operator=(Texture2D &&program) noexcept;

    Texture2D(Texture2D &&program) noexcept;

    void bind();

public:
    int width = 0;
    int height = 0;
    int channel = 0;
    GLenum format;
    GLuint textureID = 0;


};


#endif //BASEOPEGL_TEXTURE2D_H
