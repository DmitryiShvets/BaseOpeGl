//
// Created by Dmitry on 14.06.2022.
//

#include "Object2D.h"

Object2D::Object2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation) : mPosition(mPosition), mSize(mSize), mRotation(mRotation) {}

void Object2D::setPosition(const glm::vec2 &pos) {
    mPosition = pos;
}

void Object2D::setSize(const glm::vec2 &size) {
    mSize = size;
}

void Object2D::setRotation(float angle) {
    mRotation = angle;
}

glm::vec2 Object2D::position() {
    return mPosition;
}

glm::vec2 Object2D::size() {
    return mSize;
}

float Object2D::rotation() {
    return mRotation;
}


