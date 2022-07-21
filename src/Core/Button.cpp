//
// Created by dmirty on 20.07.2022.
//

#include "Button.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Render.h"
#include "TextRender.h"

Button::Button(const std::wstring &content, const glm::vec2 &position, const glm::vec2 &size) : mContent(std::move(content)), mPos(position),
                                                                                                mSize(size) {

    program->use();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
    program->setUniform("projectionMatrix", projection);
    program->setUniform("color", glm::vec3(0.6f, 0.6f, 0.65f));
    program->unbind();

}

void Button::render() {
    //auto &program = game.resourceManager.getProgram("defaultControl");

    program->use();
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPos, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));

    program->setUniform("modelMatrix", modelMatrix);
    Renderer::draw(mVAO);
    program->unbind();

    if (!mContent.empty()) TextRenderer::draw(mContent, mPos.x + 20, mPos.y + 10, 0.4f, 20.0f, glm::vec3(1.0f, 0.8f, 0.2f));

}
