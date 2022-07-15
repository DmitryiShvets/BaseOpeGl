//
// Created by Dmitry on 14.06.2022.
//

#ifndef BASEOPEGL_SPRITE2D_H
#define BASEOPEGL_SPRITE2D_H


#include <GL/glew.h>
#include <string>

#include "MultiTexture2D.h"
#include "ShaderProgram.h"


class Sprite2D  {
public:
    //Sprite2D(const Texture2D &texture, const ShaderProgram &programName, const glm::vec2 &position, const glm::vec2 &size, float rotation);

    Sprite2D(Texture2D *texture, ShaderProgram *program);

    Sprite2D( MultiTexture2D *texture, ShaderProgram *program,const size_t &subTexName=1);

    void render(const glm::vec2 &position, const glm::vec2 &size, float rotation,const size_t frameId);

    virtual ~Sprite2D();

private:
    Texture2D *mTexture;
    ShaderProgram *mProgram;
    //  ResourceManager &resourceManager;
    GLuint mVAO;
    GLuint mVerCoordVBO;
    GLuint mVerColorVBO;
    size_t mLastFrameId;

};


#endif //BASEOPEGL_SPRITE2D_H
