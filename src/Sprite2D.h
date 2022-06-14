//
// Created by Dmitry on 14.06.2022.
//

#ifndef BASEOPEGL_SPRITE2D_H
#define BASEOPEGL_SPRITE2D_H

#include "Object2D.h"
#include <GL/glew.h>
#include <string>
#include "ResourceManager.h"

class Sprite2D : public Object2D {
public:
    Sprite2D(const std::string &textureName, const std::string &programName, const glm::vec2 &position, const glm::vec2 &size, float rotation, ResourceManager &manager = ResourceManager::getInstance());

    void render();

    virtual ~Sprite2D();

private:
    std::string mTextureName;
    std::string mProgramName;
    ResourceManager &resourceManager;
    GLuint mVAO;
    GLuint mVerCoordVBO;
    GLuint mVerColorVBO;


};


#endif //BASEOPEGL_SPRITE2D_H
