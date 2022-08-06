//
// Created by Dmitry on 27.07.2022.
//

#include "SquareNode.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Render/Render.h"
#include "../Core/EventManager.h"


void SquareNode::render() {

    if (mSelected)mColor = glm::vec3(0.92f, 0.67f, 0.25f); //При выборе поля
    if (!mSelected && mHover)mColor = glm::vec3(0.0f, 0.75f, 0.0f); //При наведении
    if (!mSelected && !mHover)mColor = mDefaultColor; //По умолчанию


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

    if (mFigure) mFigure->render();
}


SquareNode::SquareNode(const std::string &name, const glm::vec2 &position, ChessFraction color) : Object2D(position, glm::vec2(100, 100), 0.f),
                                                                                                  mFraction(color), mNodeName(name) {

    if (mFraction == ChessFraction::WHITE)mDefaultColor = glm::vec3(0.95f, 0.85f, 0.65f);
    if (mFraction == ChessFraction::BLACK)mDefaultColor = glm::vec3(0.44f, 0.35f, 0.16f);


    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(900 ), 0.0f, static_cast<float>(900));

    mProgram->use();
    mProgram->setUniform("vertexColor", mColor);
    mProgram->setUniform("projectionMatrix", projection);
    mProgram->unbind();

    EventManager::getInstance().subscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::NODE_UNSELECTED_EVENT, this);
}

void SquareNode::update(Event *e) {
    if (e->getType() == Event::EventType::MOUSE_MOVED_EVENT) {
        auto *event = dynamic_cast<MouseMovedEvent * >(e);
        if (isPointOn(event->x, event->y)) mHover = true;
        else mHover = false;
    }
    if (e->getType() == Event::EventType::MOUSE_BUTTON_PRESSED_EVENT) {
        auto *event = dynamic_cast<MouseButtonPressedEvent * >(e);
        if (isPointOn(event->x, event->y)) {
            mSelected = true;
            mSelectedNode = this->mNodeName;
            NodeSelectedEvent ev(mNodeName);
            EventManager::eventRoute(&ev);

        } else {
            mSelected = false;
            mSelectedNode.clear();
        }

    }
    if (e->getType() == Event::EventType::NODE_UNSELECTED_EVENT) {
        auto *event = dynamic_cast<NodeUnselectedEvent * >(e);
        if (event->nodeName == mNodeName)mSelected = false;
    }

}

SquareNode::~SquareNode() {
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
    EventManager::getInstance().unsubscribe(Event::EventType::NODE_UNSELECTED_EVENT, this);
    if (mFigure) delete mFigure;
}

SquareNode &SquareNode::operator=(SquareNode &&node) noexcept {
    if (this != &node) {
        mColor = node.mColor;
        mDefaultColor = node.mDefaultColor;
        mSelected = node.mSelected;
        mHover = node.mHover;
        mFraction = node.mFraction;
        mNodeName = node.mNodeName;
        mFigure = node.mFigure;
        mSelectedNode = node.mSelectedNode;

        mProgram = node.mProgram;
        mVAO = node.mVAO;

        node.mFigure = nullptr;
        node.mProgram = nullptr;
        node.mVAO = nullptr;

        EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_MOVED_EVENT, &node);
        EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, &node);
        EventManager::getInstance().unsubscribe(Event::EventType::NODE_UNSELECTED_EVENT, this);

        EventManager::getInstance().subscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
        EventManager::getInstance().subscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
        EventManager::getInstance().subscribe(Event::EventType::NODE_UNSELECTED_EVENT, this);
    }
    return *this;
}

SquareNode::SquareNode(SquareNode &&node) noexcept: Object2D(std::move(node)) {
    mColor = node.mColor;
    mDefaultColor = node.mDefaultColor;
    mSelected = node.mSelected;
    mHover = node.mHover;
    mFraction = node.mFraction;
    mNodeName = node.mNodeName;
    mFigure = node.mFigure;
    mSelectedNode = node.mSelectedNode;

    mProgram = node.mProgram;
    mVAO = node.mVAO;

    node.mFigure = nullptr;
    node.mProgram = nullptr;
    node.mVAO = nullptr;

    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_MOVED_EVENT, &node);
    EventManager::getInstance().unsubscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, &node);
    EventManager::getInstance().unsubscribe(Event::EventType::NODE_UNSELECTED_EVENT, this);

    EventManager::getInstance().subscribe(Event::EventType::MOUSE_MOVED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::NODE_UNSELECTED_EVENT, this);
}

void SquareNode::setFigure(Figure::FigureType type, int side) {
    mFigure = new Figure(side, type, glm::vec2(mPosition.x + 10, mPosition.y + 3));
}

void SquareNode::deleteFigure() {
    mFigure = nullptr;
}

void SquareNode::swapFigure(Figure *figure) {
    delete mFigure;
    mFigure = figure;
    mFigure->setPosition(glm::vec2(mPosition.x + 10, mPosition.y + 3));
}
