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
#include "Figure.h"

enum class ChessFraction {
    BLACK = 0, WHITE = 1
};

class SquareNode : public Object2D, Subscriber {
public:
    SquareNode(const glm::vec2 &mPosition, const glm::vec2 &mSize, ChessFraction color);

    void render();

    void update(Event *e) override;

    void setFigure(Figure::FigureType type, int side);

    void swapFigure(Figure *figure);

    void deleteFigure();

    ~SquareNode() override;

    SquareNode() = delete;

    SquareNode(SquareNode &) = delete;

    SquareNode &operator=(const SquareNode &) = delete;

    SquareNode &operator=(SquareNode &&node) noexcept;

    SquareNode(SquareNode &&node) noexcept;

    Figure *mFigure = nullptr;
private:
    glm::vec3 mColor;
    glm::vec3 mDefaultColor;

    ChessFraction mFraction;

    bool mHover = false;
    bool mSelected = false;

    VAO *mVAO = &ResourceManager::getInstance().baseVAO;
    ShaderProgram *mProgram = &ResourceManager::getInstance().getProgram("default");

};


#endif //BASEOPEGL_SQUARENODE_H
