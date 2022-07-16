//
// Created by Dmitry on 14.06.2022.
//

#ifndef BASEOPEGL_OBJECT2D_H
#define BASEOPEGL_OBJECT2D_H

#include "glm/vec2.hpp"

class Object2D {
public:
    Object2D(const glm::vec2 &mPosition, const glm::vec2 &mSize, float mRotation);

    virtual void setPosition(const glm::vec2 &pos);

    virtual void setSize(const glm::vec2 &size);

    virtual void setRotation(float angle);

    virtual glm::vec2 position();

    virtual glm::vec2 size();

    virtual float rotation();

protected:
    glm::vec2 mPosition;
    glm::vec2 mSize;
    float mRotation;
};


#endif //BASEOPEGL_OBJECT2D_H
