//
// Created by Dmitry on 27.07.2022.
//

#ifndef BASEOPEGL_SQUARENODE_H
#define BASEOPEGL_SQUARENODE_H

#include "../Render/Object2D.h"
#include "../Render/ShaderProgram.h"
#include "../Render/BufferObjects.h"
#include "../Core/ResourceManager.h"
#include "../Core/Subscriber.h"
#include "Figure.h"

enum class ChessFraction {
    BLACK = 0, WHITE = 1
};

class SquareNode : public Object2D, Subscriber {
public:
    SquareNode(const std::string &name, const glm::vec2 &mPosition, ChessFraction color);

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

    std::string mNodeName;
    glm::vec3 mColor;
    glm::vec3 mDefaultColor;


    ChessFraction mFraction;
    bool mActive = true;
    bool mHover = false;
    bool mSelected = false;

    VAO *mVAO = &ResourceManager::getInstance().baseVAO;
    ShaderProgram *mProgram = &ResourceManager::getInstance().getProgram("default");

    std::string mSelectedNode;

};


#endif //BASEOPEGL_SQUARENODE_H
