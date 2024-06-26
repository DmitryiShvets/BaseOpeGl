//
// Created by dmirty on 20.07.2022.
//

#include "Button.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Render/Render.h"
#include "../Render/TextRender.h"

Button::Button(std::wstring content, const glm::vec2 &position, const glm::vec2 &size) : Subscriber(), Object2D(position, size, 0),
                                                                                         mContent(std::move(content)) {

    program->use();
    mDefaultColor = glm::vec3(0.6f, 0.6f, 0.65f);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(900), 0.0f, static_cast<float>(900));
    program->setUniform("projectionMatrix", projection);
    program->setUniform("color", mDefaultColor);
    program->unbind();


    EventManager::getInstance().subscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::MOUSE_MOVED_EVENT, this);

}

void Button::render() {
    //auto &program = game.resourceManager.getProgram("defaultControl");

    mColor = mDefaultColor;
    if (mHover)mColor = glm::vec3(0.0f, 0.75f, 0.0f); //При наведении


    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));

    program->use();
    program->setUniform("color", mColor);
    program->setUniform("modelMatrix", modelMatrix);
    Renderer::draw(mVAO);
    program->unbind();

   // if (!mContent.empty()) TextRenderer::draw(mContent, mPosition.x + 20, mPosition.y + 10, 0.4f, 20.0f, glm::vec3(1.0f, 0.8f, 0.2f));
    if (!mContent.empty()) TextRenderer::draw(mContent,( (2 * mPosition.x + mSize.x) / 2)-(mContent.size()*10/2), ((2 * mPosition.y + mSize.y) / 2)-7, 0.4f, 20.0f, glm::vec3(1.0f, 0.8f, 0.2f));

}


void Button::onMouseBtnPressed(int button, double x, double y) {
    if (isPointOn(x, y) && button == 0)onClick();
}

Button::~Button() {
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
}

void Button::update(Event *e) {
    if (mActive) {
        if (e->getType() == Event::EventType::MOUSE_BUTTON_PRESSED_EVENT) {
            auto *event = dynamic_cast<MouseButtonPressedEvent * >(e);
            onMouseBtnPressed(event->button, event->x, event->y);
        }
        if (e->getType() == Event::EventType::MOUSE_MOVED_EVENT) {
            auto *event = dynamic_cast<MouseMovedEvent * >(e);
            if (isPointOn(event->x, event->y)) mHover = true;
            else mHover = false;
        }
    }
}


