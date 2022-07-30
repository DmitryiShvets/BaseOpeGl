//
// Created by Dmitry on 27.07.2022.
//

#include "SquareNode.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Core/Render.h"
#include "../Core/EventManager.h"

void SquareNode::render() {

    if (selected)color = glm::vec3(0.6f, 0.6f, 0.65f); //При выборе поля
    if (!selected && hover)color = glm::vec3(0.0f, 1.0f, 0.0f); //При наведении
    if (!selected && !hover)color = defaultColor; //По умолчанию


    glm::mat4 modelMatrix(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPosition, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));


    mProgram->use();
    mProgram->setUniform("vertexColor", color);
    mProgram->setUniform("modelMatrix", modelMatrix);
    Renderer::draw(mVAO);
    mProgram->unbind();
}


SquareNode::SquareNode(const glm::vec2 &mPosition, const glm::vec2 &mSize, ChessFraction _fraction) : Object2D(mPosition, mSize, 0.f),
                                                                                                      fraction(_fraction) {

    if (fraction == ChessFraction::WHITE)defaultColor = glm::vec3(1.0, 1.0, 1.0);
    if (fraction == ChessFraction::BLACK)defaultColor = glm::vec3(0.0, 0.0, 0.0);


    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));

    mProgram->use();
    mProgram->setUniform("vertexColor", color);
    mProgram->setUniform("projectionMatrix", projection);
    mProgram->unbind();

    EventManager::getInstance().subscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
}

void SquareNode::update(Event *e) {
    if (e->getType() == Event::EventType::MOUSE_MOVED_EVENT) {
        auto *event = dynamic_cast<MouseMovedEvent * >(e);
        if (isPointOn(event->x, event->y)) hover = true;
        else hover = false;
    }
    if (e->getType() == Event::EventType::MOUSE_BUTTON_PRESSED_EVENT) {
        auto *event = dynamic_cast<MouseButtonPressedEvent * >(e);
        if (isPointOn(event->x, event->y))selected = !selected;
        else selected = false;
    }

}

SquareNode::~SquareNode() {
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
}
