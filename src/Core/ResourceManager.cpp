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

void ResourceManager::init() {

    shaderPrograms.emplace("default", ShaderProgram(readFile("res/defaultVER.glsl"), readFile("res/defaultFRG.glsl")));
    shaderPrograms.emplace("defaultSprite",
                           ShaderProgram(readFile("res/defaultSpriteVER.glsl"), readFile("res/defaultSpriteFRG.glsl")));
    shaderPrograms.emplace("defaultText", ShaderProgram(readFile("res/textVER.glsl"), readFile("res/textFRG.glsl")));
    shaderPrograms.emplace("defaultControl", ShaderProgram(readFile("res/controlVER.glsl"), readFile("res/controlFRG.glsl")));


    textures.emplace("default", Texture2D("res/awesomeface.png"));
    textures.emplace("defaultSprite", Texture2D("res/image.png"));
    textures.emplace("b_bishop", Texture2D("res/b_bishop_png_shadow_128px.png"));
    textures.emplace("b_king", Texture2D("res/b_king_png_shadow_128px.png"));
    textures.emplace("b_knight", Texture2D("res/b_knight_png_shadow_128px.png"));
    textures.emplace("b_pawn", Texture2D("res/b_pawn_png_shadow_128px.png"));
    textures.emplace("b_queen", Texture2D("res/b_queen_png_shadow_128px.png"));
    textures.emplace("b_rook", Texture2D("res/b_rook_png_shadow_128px.png"));
    textures.emplace("fon_light", Texture2D("res/square_gray_light_png_shadow_128px.png"));
    textures.emplace("fon_dark", Texture2D("res/square_gray_dark_png_shadow_128px.png"));

    mMulTextures.emplace("defaultSprite", MultiTexture2D("res/atlas.png", {1, 2, 3, 4, 5}, 200, 150));


    mFonts.emplace("Open-Sans", Font("res/fonts/OpenSans-Bold.ttf"));

    const GLfloat vertex[] = {
            //x(s)  y(t)
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
    };

    baseVAO.bind();

    VBO mVBO;
    mVBO.init(vertex, 2 * 6 * sizeof(GLfloat));

    VBOLayout menuVBOLayout;
    menuVBOLayout.addLayoutElement(2, GL_FLOAT, GL_FALSE);

    baseVAO.addBuffer(mVBO, menuVBOLayout, 6);

    mVBO.unbind();
    baseVAO.unbind();


}

void ResourceManager::destroy() {
    //std::cout << "Destructor ResourceManager (" << this << ") called " << std::endl;
    shaderPrograms.clear();
    textures.clear();
    mMulTextures.clear();
    // mSprites.clear();
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

//Sprite2D &ResourceManager::getSprite(const std::string &textureName) {
//    auto it = mSprites.find(textureName);
//    if (it != mSprites.end()) {
//        return it->second;
//    }
//    return mSprites.find("defaultSprite")->second;
//}

Font &ResourceManager::getFont(const std::string &fontName) {
    auto it = mFonts.find(fontName);
    if (it != mFonts.end()) {
        return it->second;
    }
    return mFonts.find("defaultSprite")->second;
}
