//
// Created by Dmitry on 27.07.2022.
//

#ifndef BASEOPEGL_SQUARENODE_H
#define BASEOPEGL_SQUARENODE_H

#include "../Core/Object2D.h"
#include "../Core/ShaderProgram.h"
#include "../Core/BufferObjects.h"
#include "../Core/ResourceManager.h"
#include "../Core/Subscriber.h"

enum class ChessFraction {
    BLACK = 0, WHITE = 1
};

class SquareNode : public Object2D, Subscriber {
public:
    SquareNode(const glm::vec2 &mPosition, const glm::vec2 &mSize, ChessFraction color);

    void render();

    void update(Event *e) override;

    ~SquareNode() override;

private:
    glm::vec3 color;
    VAO *mVAO = &ResourceManager::getInstance().baseVAO;
    ShaderProgram *mProgram = &ResourceManager::getInstance().getProgram("default");

    ChessFraction fraction;
    glm::vec3 defaultColor;

    bool hover = false;
    bool selected = false;
};


#endif //BASEOPEGL_SQUARENODE_H
