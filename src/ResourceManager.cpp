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

}

ResourceManager::~ResourceManager() {

}

void ResourceManager::Init() {

    //shaderPrograms["default"] = std::move(ShaderProgram(readFile("res/defaultVER.txt"), readFile("res/defaultFRG.txt")));

    shaderPrograms.emplace("default", ShaderProgram(readFile("res/defaultVER.glsl"), readFile("res/defaultFRG.glsl")));

}

void ResourceManager::Destroy() {
    shaderPrograms.clear();
}

void ResourceManager::useProgram(const std::string &progName) {
    if (shaderPrograms.contains(progName) && shaderPrograms[progName].isCompiled())shaderPrograms[progName].use();
    else {
        std::cerr << "USING INVALID PROGRAM ERROR" << std::endl;
        return;
    }
}

 GLuint &ResourceManager::getProgram(const std::string &progName) {
    return shaderPrograms[progName].getProgram();
}
