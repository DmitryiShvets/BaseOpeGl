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
    shaderPrograms.emplace("defaultSprite", ShaderProgram(readFile("res/defaultSpriteVER.glsl"), readFile("res/defaultSpriteFRG.glsl")));

    textures.emplace("default", Texture2D("awesomeface.png"));
    textures.emplace("defaultSprite", Texture2D("image.png"));

}

void ResourceManager::Destroy() {
    //std::cout << "Destructor ResourceManager (" << this << ") called " << std::endl;
    shaderPrograms.clear();
    textures.clear();
}

void ResourceManager::useProgram(const std::string &progName) {
    if (shaderPrograms.contains(progName) && shaderPrograms[progName].isCompiled())shaderPrograms[progName].use();
    else {
        std::cerr << "USING INVALID PROGRAM ERROR" << std::endl;
        return;
    }
}

ShaderProgram &ResourceManager::getProgram(const std::string &progName) {
    return shaderPrograms[progName];

}

ResourceManager &ResourceManager::getInstance() {
    static ResourceManager instance;

    return instance;
}

Texture2D &ResourceManager::getTexture(const std::string &textureName) {
    return textures[textureName];
}
