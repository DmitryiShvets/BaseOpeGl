//
// Created by Dmitry on 04.08.2022.
//

#ifndef BASEOPEGL_LEVEL_H
#define BASEOPEGL_LEVEL_H

#include "SquareNode.h"
#include <map>
#include <string>

class Level {
public:

    Level();

    void move(const std::string &source, const std::string &dist);

    void render();

    ~Level();

private:
    std::map<std::string, SquareNode> mLvl;

    void move(SquareNode &source, SquareNode &dist);

};


#endif //BASEOPEGL_LEVEL_H
