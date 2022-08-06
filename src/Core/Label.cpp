//
// Created by Dmitry on 06.08.2022.
//

#include "Label.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Render/Render.h"
#include "../Render/TextRender.h"

Label::Label(const glm::vec2 &position, const glm::vec2 &size, const glm::vec3 &color, std::wstring content) : Object2D(position, size, 0),
                                                                                                               mContent(std::move(content)),
                                                                                                               mColor(color) {

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(900 ), 0.0f, static_cast<float>(900));

    mProgram->use();
    mProgram->setUniform("vertexColor", mColor);
    mProgram->setUniform("projectionMatrix", projection);
    mProgram->unbind();


}

void Label::render() {
    glm::mat4 modelMatrix(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));


    mProgram->use();
    mProgram->setUniform("vertexColor", mColor);
    mProgram->setUniform("modelMatrix", modelMatrix);
    Renderer::draw(mVAO);
    mProgram->unbind();


    if (!mContent.empty())
        TextRenderer::draw(mContent,( (2 * mPosition.x + mSize.x) / 2)-7, ((2 * mPosition.y + mSize.y) / 2)-7, 0.4f, 20.0f, glm::vec3(0.1f, 0.1f, 0.1f));

}

Label::~Label() {

}

Label &Label::operator=(Label &&other) noexcept {
    if (this != &other) {
        mColor = other.mColor;
        mContent = std::move(other.mContent);

        mProgram = other.mProgram;
        mVAO = other.mVAO;

        other.mProgram = nullptr;
        other.mVAO = nullptr;
    }
    return *this;
}

Label::Label(Label &&other) noexcept: Object2D(std::move(other)) {
    mColor = other.mColor;
    mContent = std::move(other.mContent);

    mProgram = other.mProgram;
    mVAO = other.mVAO;

    other.mProgram = nullptr;
    other.mVAO = nullptr;
}

//Label::Label() : Object2D(glm::vec2(0, 0), glm::vec2(0, 0), 0), mColor(glm::vec3(0)) {
//
//}


