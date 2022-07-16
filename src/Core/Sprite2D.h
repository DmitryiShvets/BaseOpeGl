//
// Created by Dmitry on 14.06.2022.
//

#ifndef BASEOPEGL_SPRITE2D_H
#define BASEOPEGL_SPRITE2D_H


#include <GL/glew.h>
#include <string>
#include "Object2D.h"
#include "MultiTexture2D.h"
#include "ShaderProgram.h"


class Sprite2D : Object2D {
public:

    Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, Texture2D *texture, ShaderProgram *program);

    Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, MultiTexture2D *texture, ShaderProgram *program, const size_t &subTexName = 1);

    void render();

    void render(const glm::vec2 &position, const glm::vec2 &size, float rotation, const size_t frameId);

    virtual ~Sprite2D();

    void setPosition(const glm::vec2 &pos) override;

    void setSize(const glm::vec2 &size) override;

    void setRotation(float angle) override;

    void setCurrentFrame(size_t frameId);

    size_t getLastFrame();

    glm::vec2 position() override;

    glm::vec2 size() override;

    float rotation() override;

    Sprite2D() = delete;

    Sprite2D(Sprite2D &) = delete;

    Sprite2D &operator=(const Sprite2D &) = delete;

    Sprite2D &operator=(Sprite2D &&sprite2D) noexcept;

    Sprite2D(Sprite2D &&sprite2D) noexcept;


private:
    Texture2D *mTexture;
    ShaderProgram *mProgram;
    //  ResourceManager &resourceManager;
    GLuint mVAO;
    GLuint mVerCoordVBO;
    GLuint mVerColorVBO;
    size_t mLastFrameId = 0;
    size_t mCurrentFrameId;

};


#endif //BASEOPEGL_SPRITE2D_H
