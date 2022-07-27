//
// Created by Dmitry on 27.07.2022.
//

#ifndef BASEOPEGL_SQUARENODE_H
#define BASEOPEGL_SQUARENODE_H

#include "../Core/Object2D.h"
#include "../Core/ShaderProgram.h"
#include "../Core/BufferObjects.h"
#include "../Core/ResourceManager.h"


class SquareNode : public Object2D {
public:
    SquareNode(const glm::vec2 &mPosition, const glm::vec2 &mSize);

    void render();

private:

    VAO *mVAO = &ResourceManager::getInstance().baseVAO;
    ShaderProgram *mProgram = &ResourceManager::getInstance().getProgram("default");

};


#endif //BASEOPEGL_SQUARENODE_H
