//
// Created by Dmitry on 14.06.2022.
//

#include "Sprite2D.h"
#include "ResourceManager.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sprite2D::Sprite2D(const std::string &textureName, const std::string &programName, const glm::vec2 &position, const glm::vec2 &size, float rotation, ResourceManager &manager) : mTextureName(
        textureName), mProgramName(programName), resourceManager(manager), Object2D(position, size, rotation) {
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


    resourceManager.getProgram(mProgramName).use();

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));

    glBindVertexArray(mVAO);
    resourceManager.getProgram(mProgramName).setUniform("modelMatrix", modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    resourceManager.getTexture(mTextureName).bind();
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
