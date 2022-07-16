//
// Created by Dmitry on 16.07.2022.
//

#ifndef BASEOPEGL_GAME_H
#define BASEOPEGL_GAME_H

#include "../Core/Sprite2D.h"
#include "../Core/SpriteAnimator.h"
#include "../Core/ResourceManager.h"
#include <glm/vec2.hpp>

#include <vector>


class Game {
public:
    Game(glm::ivec2 windowSize);

    ~Game();

    void render();

    void update(unsigned long long delta);

    void init();

    ResourceManager &resourceManager;

private:
    glm::ivec2 mWindowSize;
    std::vector<Sprite2D> mVecSprites;
    std::vector<SpriteAnimator> mVecSpriteAnimators;

};


#endif //BASEOPEGL_GAME_H
