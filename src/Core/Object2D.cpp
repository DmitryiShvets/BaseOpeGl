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

bool Object2D::isPointOn(double x, double y) {
    return (x >= mPosition.x) && (x <= mPosition.x + mSize.x) && (y >= mPosition.y) && (y <= mPosition.y + mSize.y);
}

Object2D &Object2D::operator=(Object2D &&object2D) noexcept {
    if (this != &object2D) {
        mPosition = object2D.mPosition;
        mRotation = object2D.mRotation;
        mSize = object2D.mSize;

    }
    return *this;
}

Object2D::Object2D(Object2D &&object2D) noexcept {
    mPosition = object2D.mPosition;
    mRotation = object2D.mRotation;
    mSize = object2D.mSize;
}


