//
// Created by Dmitry on 11.06.2022.
//

#include <iostream>
#include <fstream>

#include "ResourceManager.h"

static std::string readFile(const std::string &path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
                  << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string{(std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>()};
}

ResourceManager::ResourceManager() {
    std::cout << "Constructor ResourceManager (" << this << ") called " << std::endl;
}

ResourceManager::~ResourceManager() {
    std::cout << "Destructor ResourceManager (" << this << ") called " << std::endl;
}

void ResourceManager::Init() {

    shaderPrograms.emplace("default", ShaderProgram(readFile("res/defaultVER.glsl"), readFile("res/defaultFRG.glsl")));
    shaderPrograms.emplace("defaultSprite",
                           ShaderProgram(readFile("res/defaultSpriteVER.glsl"), readFile("res/defaultSpriteFRG.glsl")));
    shaderPrograms.emplace("defaultText", ShaderProgram(readFile("res/textVER.glsl"), readFile("res/textFRG.glsl")));
    shaderPrograms.emplace("defaultControl", ShaderProgram(readFile("res/controlVER.glsl"), readFile("res/controlFRG.glsl")));

    textures.emplace("default", Texture2D("awesomeface.png"));
    textures.emplace("defaultSprite", Texture2D("image.png"));

    mMulTextures.emplace("defaultSprite", MultiTexture2D("atlas.png", {1, 2, 3, 4, 5}, 200, 150));

    mSprites.emplace("defaultSprite", Sprite2D(glm::vec2(100.0f, 100.0f), glm::vec2(100.0f, 100.0f), 0,
                                               &getMultiTexture("defaultSprite"),
                                               &getProgram("defaultSprite"), 1));
    mFonts.emplace("Open-Sans", Font("res/fonts/OpenSans-Bold.ttf"));

}

void ResourceManager::Destroy() {
    //std::cout << "Destructor ResourceManager (" << this << ") called " << std::endl;
    shaderPrograms.clear();
    textures.clear();
    mMulTextures.clear();
    mSprites.clear();
    mFonts.clear();
}


ShaderProgram &ResourceManager::getProgram(const std::string &progName) {
    //return shaderPrograms[progName];
    auto it = shaderPrograms.find(progName);
    if (it != shaderPrograms.end()) {
        return it->second;
    }
    return shaderPrograms.find("default")->second;
}

ResourceManager &ResourceManager::getInstance() {
    static ResourceManager instance;

    return instance;
}

Texture2D &ResourceManager::getTexture(const std::string &textureName) {
    // return textures[textureName];
    auto it = textures.find(textureName);
    if (it != textures.end()) {
        return it->second;
    }
    return textures.find("default")->second;
}

MultiTexture2D &ResourceManager::getMultiTexture(const std::string &textureName) {
    // return mMulTextures[textureName];
    auto it = mMulTextures.find(textureName);
    if (it != mMulTextures.end()) {
        return it->second;
    }
    return mMulTextures.find("defaultSprite")->second;
}

Sprite2D &ResourceManager::getSprite(const std::string &textureName) {
    auto it = mSprites.find(textureName);
    if (it != mSprites.end()) {
        return it->second;
    }
    return mSprites.find("defaultSprite")->second;
}

Font &ResourceManager::getFont(const std::string &fontName) {
    auto it = mFonts.find(fontName);
    if (it != mFonts.end()) {
        return it->second;
    }
    return mFonts.find("defaultSprite")->second;
}
