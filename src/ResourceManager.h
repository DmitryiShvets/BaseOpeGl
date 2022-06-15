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

class ResourceManager {
public:
    static ResourceManager &getInstance();

    ~ResourceManager();

    void Init();

    void Destroy();

    ShaderProgram &getProgram(const std::string &progName);

    Texture2D &getTexture(const std::string &textureName);

    MultiTexture2D &getMultiTexture(const std::string &textureName);


private:
    ResourceManager();

    ResourceManager(ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(ResourceManager &&program) = delete;

    ResourceManager(ResourceManager &&program) = delete;

    std::map<std::string, ShaderProgram> shaderPrograms;
    std::map<std::string, Texture2D> textures;
    std::map<std::string, MultiTexture2D> mMulTextures;
};


#endif //BASEOPEGL_RESOURCEMANAGER_H
