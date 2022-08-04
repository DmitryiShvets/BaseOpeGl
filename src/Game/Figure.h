//
// Created by Dmitry on 04.08.2022.
//

#ifndef BASEOPEGL_FIGURE_H
#define BASEOPEGL_FIGURE_H

#include "../Core/Sprite2D.h"

class Figure {
public:
    enum class FigureType {
        PAWN = 1,
        ROOK,
        BISHOP,
        KNIGHT,
        KING,
        QUEEN
    };

    Figure(int side, FigureType type, const glm::vec2 &position);

    void render();

    void setPosition(const glm::vec2 &position);

    ~Figure() = default;

private:
    FigureType mType;
    Sprite2D mSprite;

};


#endif //BASEOPEGL_FIGURE_H
