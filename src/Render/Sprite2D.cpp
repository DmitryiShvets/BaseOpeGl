//
// Created by Dmitry on 14.06.2022.
//

#include "Sprite2D.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Render.h"

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

    VBOLayout mVerCoordVBOLayout;
    mVerCoordVBOLayout.addLayoutElement(2, GL_FLOAT, GL_FALSE);

    mVAO.bind();

    mVerCoordVBO.init(verVBO, 2 * 6 * sizeof(GLfloat));
    mVAO.addBuffer(mVerCoordVBO, mVerCoordVBOLayout, 6);
    mVerCoordVBO.unbind();

    mVerColorVBO.init(verVBO1, 2 * 6 * sizeof(GLfloat));
    mVAO.addBuffer(mVerColorVBO, mVerCoordVBOLayout);
    mVerColorVBO.unbind();

    mVAO.unbind();

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

        mVerColorVBO.update(verVBO1, 2 * 6 * sizeof(GLfloat));
        //  glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
        //  glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
        mVerColorVBO.unbind();
    }

    //resourceManager.getProgram(mProgram).use();
    mProgram->use();
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));

    // glBindVertexArray(mVAO);
    //resourceManager.getProgram(mProgram).setUniform("modelMatrix", modelMatrix);
    mProgram->setUniform("modelMatrix", modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    //resourceManager.getTexture(mTexture).bind();
    mTexture->bind();

    Renderer::draw(mVAO);
    //mVAO.bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    // mVAO.unbind();
    // glBindVertexArray(0);
    mTexture->unbind();
    //glBindTexture(GL_TEXTURE_2D, 0);
    mProgram->unbind();
//    glUseProgram(0);
}

Sprite2D::~Sprite2D() {
    //  glDeleteVertexArrays(1, &mVAO);
    //  glDeleteBuffers(1, &mVerCoordVBO);
    //  glDeleteBuffers(1, &mVerColorVBO);
}

Sprite2D::Sprite2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation, MultiTexture2D *mTexture, ShaderProgram *mProgram, const size_t &subTexName) : Object2D(
        mPosition, mSize, mRotation), mTexture(mTexture), mProgram(mProgram), mCurrentFrameId(subTexName) {
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
    // glGenVertexArrays(1, &mVAO);
    //  glBindVertexArray(mVAO);

    mVAO.bind();
    //glGenBuffers(1, &mVerCoordVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, mVerCoordVBO);
    //  glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO), &verVBO, GL_STATIC_DRAW);
    mVerCoordVBO.init(verVBO, 2 * 6 * sizeof(GLfloat));

    VBOLayout mVerCoordVBOLayout;
    mVerCoordVBOLayout.addLayoutElement(2, GL_FLOAT, GL_FALSE);

    mVAO.addBuffer(mVerCoordVBO, mVerCoordVBOLayout, 6);
    //glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    mVerCoordVBO.unbind();

    //glGenBuffers(1, &mVerColorVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
    mVerColorVBO.init(verVBO1, 2 * 6 * sizeof(GLfloat));

    mVAO.addBuffer(mVerColorVBO, mVerCoordVBOLayout);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    mVerColorVBO.unbind();

    //  glBindBuffer(GL_ARRAY_BUFFER, 0);
    mVAO.unbind();
    // glBindVertexArray(0);
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

        //   glBindBuffer(GL_ARRAY_BUFFER, mVerColorVBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(verVBO1), &verVBO1, GL_STATIC_DRAW);
        mVerColorVBO.update(verVBO1, 2 * 6 * sizeof(GLfloat));
        mVerColorVBO.unbind();
    }

    mProgram->use();
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

    // glBindVertexArray(mVAO);
    mProgram->setUniform("modelMatrix", modelMatrix);

    glActiveTexture(GL_TEXTURE0);
    mTexture->bind();

    Renderer::draw(mVAO);
    // mVAO.bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    // mVAO.unbind();

    //glBindVertexArray(0);
    mTexture->unbind();
//    glBindTexture(GL_TEXTURE_2D, 0);
    mProgram->unbind();
    //glUseProgram(0);

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

glm::vec2 Sprite2D::position() {
    return Object2D::position();
}

glm::vec2 Sprite2D::size() {
    return Object2D::size();
}

float Sprite2D::rotation() {
    return Object2D::rotation();
}

Sprite2D &Sprite2D::operator=(Sprite2D &&sprite2D) noexcept {
    if (this != &sprite2D) {

        // glDeleteVertexArrays(1, &mVAO);
        //     glDeleteBuffers(1, &mVerCoordVBO);
        //     glDeleteBuffers(1, &mVerColorVBO);
        mTexture = sprite2D.mTexture;
        mProgram = sprite2D.mProgram;
        mVAO = std::move(sprite2D.mVAO);
        mVerCoordVBO = std::move(sprite2D.mVerCoordVBO);
        mVerColorVBO = std::move(sprite2D.mVerColorVBO);
        mLastFrameId = sprite2D.mLastFrameId;
        mCurrentFrameId = sprite2D.mCurrentFrameId;


        //  sprite2D.mVAO = 0;
        // sprite2D.mVerCoordVBO = 0;
        //sprite2D.mVerColorVBO = 0;

    }
    return *this;
}

Sprite2D::Sprite2D(Sprite2D &&sprite2D) noexcept: Object2D(std::move(sprite2D)) {
    mTexture = sprite2D.mTexture;
    mProgram = sprite2D.mProgram;
    mVAO = std::move(sprite2D.mVAO);
    mVerCoordVBO = std::move(sprite2D.mVerCoordVBO);
    mVerColorVBO = std::move(sprite2D.mVerColorVBO);
    mLastFrameId = sprite2D.mLastFrameId;
    mCurrentFrameId = sprite2D.mCurrentFrameId;


    //sprite2D.mVAO = 0;
    //sprite2D.mVerCoordVBO = 0;
    // sprite2D.mVerColorVBO = 0;
}
