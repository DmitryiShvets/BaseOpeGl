//
// Created by Dmitry on 04.08.2022.
//

#include "Figure.h"
#include "../Core/ResourceManager.h"


Figure::Figure(int side, Figure::FigureType type, const glm::vec2 &position) : mSprite(position, glm::vec2(80, 80), 0,
                                                                                       &ResourceManager::getInstance().getTexture("default"),
                                                                                       &ResourceManager::getInstance().getProgram("defaultSprite")) {
    ResourceManager &rm = ResourceManager::getInstance();
    glm::vec2 size(40, 80);
    if (side == 0) {
        if (type == FigureType::PAWN)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("w_pawn"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::BISHOP)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("w_bishop"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::KING)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("w_king"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::KNIGHT)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("w_knight"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::QUEEN)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("w_queen"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::ROOK)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("w_rook"), &rm.getProgram("defaultSprite")));
    }
    if (side == 1) {
        if (type == FigureType::PAWN)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("b_pawn"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::BISHOP)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("b_bishop"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::KING)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("b_king"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::KNIGHT)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("b_knight"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::QUEEN)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("b_queen"), &rm.getProgram("defaultSprite")));
        if (type == FigureType::ROOK)
            mSprite = std::move(Sprite2D(position, size, 0, &rm.getTexture("b_rook"), &rm.getProgram("defaultSprite")));
    }
}


void Figure::render() {
    mSprite.render();
}

void Figure::setPosition(const glm::vec2 &position) {
    mSprite.setPosition(position);
}
