//
// Created by Dmitry on 04.08.2022.
//

#ifndef BASEOPEGL_LEVEL_H
#define BASEOPEGL_LEVEL_H

#include "SquareNode.h"
#include "greko.h"
#include <map>
#include <string>
#include "../Core/Label.h"

class Level : Subscriber {
public:

    Level();

    void move(const std::string &source, const std::string &dist);

    void render();

    ~Level();

private:
    std::map<std::string, SquareNode> mLvl;
    std::vector<Label> mLabels;

    static

    void move(SquareNode &source, SquareNode &dist);

    void update(Event *e) override;

    std::string mCurrentSelectedNode;

    Greko greko;


    void threadTask();
};


#endif //BASEOPEGL_LEVEL_H
