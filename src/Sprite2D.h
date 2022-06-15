//
// Created by Dmitry on 14.06.2022.
//

#ifndef BASEOPEGL_SPRITE2D_H
#define BASEOPEGL_SPRITE2D_H

#include "Object2D.h"
#include <GL/glew.h>
#include <string>

#include "MultiTexture2D.h"
#include "ShaderProgram.h"


class Sprite2D : public Object2D {
public:
    //Sprite2D(const Texture2D &texture, const ShaderProgram &programName, const glm::vec2 &position, const glm::vec2 &size, float rotation);

    Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, Texture2D *mTexture, ShaderProgram *mProgram);

    Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, MultiTexture2D *mTexture, ShaderProgram *mProgram,const std::string &subTexName="default");

    virtual ~Sprite2D();

    void render();


private:
    Texture2D *mTexture;
    ShaderProgram *mProgram;
    //  ResourceManager &resourceManager;
    GLuint mVAO;
    GLuint mVerCoordVBO;
    GLuint mVerColorVBO;


};


#endif //BASEOPEGL_SPRITE2D_H
