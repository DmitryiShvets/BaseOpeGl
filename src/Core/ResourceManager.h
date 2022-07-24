//
// Created by Dmitry on 11.06.2022.
//

#ifndef BASEOPEGL_RESOURCEMANAGER_H
#define BASEOPEGL_RESOURCEMANAGER_H

#include <string>
#include <map>
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "MultiTexture2D.h"
#include "Sprite2D.h"
#include "Font.h"
#include "BufferObjects.h"

class ResourceManager {
public:
    static ResourceManager &getInstance();

    ~ResourceManager();

    void init();

    void destroy();

    ShaderProgram &getProgram(const std::string &progName);

    Texture2D &getTexture(const std::string &textureName);

    MultiTexture2D &getMultiTexture(const std::string &textureName);

    Font &getFont(const std::string &fontName);

    VAO baseVAO;

private:
    ResourceManager();

    ResourceManager(ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(ResourceManager &&program) = delete;

    ResourceManager(ResourceManager &&program) = delete;

    std::map<std::string, ShaderProgram> shaderPrograms;
    std::map<std::string, Texture2D> textures;
    std::map<std::string, MultiTexture2D> mMulTextures;
    std::map<std::string, Font> mFonts;

};


#endif //BASEOPEGL_RESOURCEMANAGER_H
