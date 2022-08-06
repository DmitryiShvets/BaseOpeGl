//
// Created by Dmitry on 16.07.2022.
//

#ifndef BASEOPEGL_GAME_H
#define BASEOPEGL_GAME_H

#include "../Render/Sprite2D.h"
#include "../Render/SpriteAnimator.h"
#include "../Core/ResourceManager.h"
#include <glm/vec2.hpp>
#include "Level.h"

#include <vector>


class Game  {
public:
    static Game &getInstance();

    ~Game();

    void render();

    void update(unsigned long long delta);

    void init();

    void destroy();

    Sprite2D &getSprite(const std::string &textureName);

private:
    Game(glm::ivec2 windowSize);

    glm::ivec2 mWindowSize;
    //std::vector<Sprite2D> mVecSprites;
    std::vector<SpriteAnimator> mVecSpriteAnimators;
    std::map<std::string, Sprite2D> mSprites;

    ResourceManager *resourceManager = nullptr;

    Level *mLvl = nullptr;


};


#endif //BASEOPEGL_GAME_H
