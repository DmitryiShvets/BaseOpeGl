//
// Created by Dmitry on 27.07.2022.
//

#include "SquareNode.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Core/Render.h"

void SquareNode::render() {
    mProgram->use();
    Renderer::draw(mVAO);
    mProgram->unbind();
}


SquareNode::SquareNode(const glm::vec2 &mPosition, const glm::vec2 &mSize) : Object2D(mPosition, mSize, 0.f) {

    glm::mat4 modelMatrix(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));

    mProgram->use();
    mProgram->setUniform("vertexColor", glm::vec3(1.0, 1.0, 1.0));
    mProgram->setUniform("projectionMatrix", projection);
    mProgram->setUniform("modelMatrix", modelMatrix);
    mProgram->unbind();
}
