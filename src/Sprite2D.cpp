//
// Created by Dmitry on 14.06.2022.
//

#include "Sprite2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sprite2D::Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, Texture2D *mTexture, ShaderProgram *mProgram) : Object2D(
        mPosition, mSize, mRotation), mTexture(mTexture), mProgram(mProgram) {
    const GLfloat verVBO[] = {
            //x(s)  y(t)
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
    };
    const GLfloat verVBO1[] = {
            //x(s)  y(t)
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
    };
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVerCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVerCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO), &verVBO, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


    glGenBuffers(1, &mVerColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


void Sprite2D::render() {
    if (mLastFrameId != mCurrentFrameId) {
        mLastFrameId = mCurrentFrameId;
        auto subTexture = mTexture->getSubTexture(mCurrentFrameId);
        const GLfloat verVBO1[] = {
                //x(s)  y(t)
                subTexture.leftBottom.x, subTexture.leftBottom.y,
                subTexture.leftBottom.x, subTexture.rightTop.y,
                subTexture.rightTop.x, subTexture.rightTop.y,

                subTexture.rightTop.x, subTexture.rightTop.y,
                subTexture.rightTop.x, subTexture.leftBottom.y,
                subTexture.leftBottom.x, subTexture.leftBottom.y,
        };

        glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
    }

    //resourceManager.getProgram(mProgram).use();
    mProgram->use();
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));

    glBindVertexArray(mVAO);
    //resourceManager.getProgram(mProgram).setUniform("modelMatrix", modelMatrix);
    mProgram->setUniform("modelMatrix", modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    //resourceManager.getTexture(mTexture).bind();
    mTexture->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

Sprite2D::~Sprite2D() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVerCoordVBO);
    glDeleteBuffers(1, &mVerColorVBO);
}

Sprite2D::Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, MultiTexture2D *mTexture, ShaderProgram *mProgram, const size_t &subTexName) : Object2D(
        mPosition, mSize, mRotation), mTexture(mTexture), mProgram(mProgram) {
    const GLfloat verVBO[] = {
            //x(s)  y(t)
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
    };
    auto subTexture = mTexture->getSubTexture(subTexName);
    const GLfloat verVBO1[] = {
            //x(s)  y(t)
            subTexture.leftBottom.x, subTexture.leftBottom.y,
            subTexture.leftBottom.x, subTexture.rightTop.y,
            subTexture.rightTop.x, subTexture.rightTop.y,

            subTexture.rightTop.x, subTexture.rightTop.y,
            subTexture.rightTop.x, subTexture.leftBottom.y,
            subTexture.leftBottom.x, subTexture.leftBottom.y,
    };
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVerCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVerCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO), &verVBO, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


    glGenBuffers(1, &mVerColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite2D::render(const glm::vec2 &position, const glm::vec2 &size, float rotation, const size_t frameId) {

    if (mLastFrameId != frameId) {
        mLastFrameId = frameId;
        auto subTexture = mTexture->getSubTexture(frameId);
        const GLfloat verVBO1[] = {
                //x(s)  y(t)
                subTexture.leftBottom.x, subTexture.leftBottom.y,
                subTexture.leftBottom.x, subTexture.rightTop.y,
                subTexture.rightTop.x, subTexture.rightTop.y,

                subTexture.rightTop.x, subTexture.rightTop.y,
                subTexture.rightTop.x, subTexture.leftBottom.y,
                subTexture.leftBottom.x, subTexture.leftBottom.y,
        };

        glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
    }

    mProgram->use();
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

    glBindVertexArray(mVAO);
    mProgram->setUniform("modelMatrix", modelMatrix);

    glActiveTexture(GL_TEXTURE0);
    mTexture->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

}

void Sprite2D::setPosition(const glm::vec2 &pos) {
    Object2D::setPosition(pos);
}

void Sprite2D::setSize(const glm::vec2 &size) {
    Object2D::setSize(size);
}

void Sprite2D::setRotation(float angle) {
    Object2D::setRotation(angle);
}

size_t Sprite2D::getLastFrame() {
    return mLastFrameId;
}

void Sprite2D::setCurrentFrame(size_t frameId) {
    mCurrentFrameId = frameId;
}
