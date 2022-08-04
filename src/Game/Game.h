//
// Created by Dmitry on 16.07.2022.
//

#ifndef BASEOPEGL_GAME_H
#define BASEOPEGL_GAME_H

#include "../Core/Sprite2D.h"
#include "../Core/SpriteAnimator.h"
#include "../Core/ResourceManager.h"
#include <glm/vec2.hpp>
#include "Level.h"
#include "../Core/Menu.h"
#include <vector>


class Game : public Subscriber {
public:
    static Game &getInstance();

    ~Game();

    void render();

    void update(unsigned long long delta);

    void init();

    void destroy();

    Sprite2D &getSprite(const std::string &textureName);

    void update(Event *e) override;

    Core::Event<void> closeEventHandler;


private:
    Game(glm::ivec2 windowSize);

    glm::ivec2 mWindowSize;
    //std::vector<Sprite2D> mVecSprites;
    std::vector<SpriteAnimator> mVecSpriteAnimators;
    std::map<std::string, Sprite2D> mSprites;

    ResourceManager *resourceManager = nullptr;

    Level *mLvl = nullptr;

    Menu *menu = nullptr;

    bool mGamePaused = false;

};


#endif //BASEOPEGL_GAME_H
