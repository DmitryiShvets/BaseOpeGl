//
// Created by Dmitry on 16.07.2022.
//

#include "Game.h"

#include <glm/gtc/matrix_transform.hpp>


bool BtnPressed(int x, int y, Sprite2D &sprite2D);

void Game::init() {

    resourceManager = &ResourceManager::getInstance();

    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(mWindowSize.x), 0.0f, static_cast<float>(mWindowSize.y), -100.f, 100.f);

    resourceManager->getProgram("defaultSprite").use();
    resourceManager->getProgram("defaultSprite").setUniform("ourTexture", 0);
    resourceManager->getProgram("defaultSprite").setUniform("projectionMatrix", projectionMatrix);
    glUseProgram(0);

    mSprites.emplace("defaultSprite", Sprite2D(glm::vec2(100.0f, 100.0f), glm::vec2(100.0f, 100.0f), 0,
                                               &resourceManager->getMultiTexture("defaultSprite"),
                                               &resourceManager->getProgram("defaultSprite"), 1));


    mVecSpriteAnimators.emplace_back(&getSprite("defaultSprite"), 1, 3, true);

}

void Game::render() {
    for (auto &mVecSprite: mSprites) {
        mVecSprite.second.render();
    }

}

void Game::update(unsigned long long delta) {
    for (auto &mVecSpriteAnimator: mVecSpriteAnimators) {
        mVecSpriteAnimator.update(delta);
    }

}

Game::Game(glm::ivec2 windowSize) : mWindowSize(windowSize) {

}

Game::~Game() {}

Sprite2D &Game::getSprite(const std::string &textureName) {

    auto it = mSprites.find(textureName);
    if (it != mSprites.end()) {
        return it->second;
    }
    return mSprites.find("defaultSprite")->second;

}

Game &Game::getInstance() {
    static Game instance(glm::ivec2(800, 600));

    return instance;
}

void Game::destroy() {
    mSprites.clear();
    mVecSpriteAnimators.clear();
}



