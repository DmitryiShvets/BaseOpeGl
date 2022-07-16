//
// Created by Dmitry on 16.07.2022.
//

#include "Game.h"
#include "../Core/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>


bool BtnPressed(int x, int y, Sprite2D &sprite2D);

void Game::init() {
    resourceManager.Init();

    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(mWindowSize.x), 0.0f, static_cast<float>(mWindowSize.y), -100.f, 100.f);

    resourceManager.getProgram("defaultSprite").use();
    resourceManager.getProgram("defaultSprite").setUniform("ourTexture", 0);
    resourceManager.getProgram("defaultSprite").setUniform("projectionMatrix", projectionMatrix);
    glUseProgram(0);


    resourceManager.getSprite("defaultSprite").setSize(glm::vec2(200.0f, 200.0f));


    mVecSpriteAnimators.emplace_back(&resourceManager.getSprite("defaultSprite"), 1, 3, true);

}

void Game::render() {
    for (auto &mVecSprite: resourceManager.mSprites) {
        mVecSprite.second.render();
    }

}

void Game::update(unsigned long long delta) {
    for (auto &mVecSpriteAnimator: mVecSpriteAnimators) {
        mVecSpriteAnimator.update(delta);
    }

}

Game::Game(glm::ivec2 windowSize) : mWindowSize(windowSize), resourceManager(ResourceManager::getInstance()) {

}

Game::~Game() {
    //ResourceManager &resourceManager = ResourceManager::getInstance();
    resourceManager.Destroy();
    mVecSprites.clear();
    mVecSpriteAnimators.clear();
}



