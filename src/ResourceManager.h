//
// Created by Dmitry on 11.06.2022.
//

#ifndef BASEOPEGL_RESOURCEMANAGER_H
#define BASEOPEGL_RESOURCEMANAGER_H

#include <string>
#include <map>
#include "ShaderProgram.h"

class ResourceManager {
public:
    ResourceManager();

    ~ResourceManager();

    void Init();

    void Destroy();

    void useProgram(const std::string &progName);

    GLuint &getProgram(const std::string &progName);

private:
    std::map<std::string, ShaderProgram> shaderPrograms;
};


#endif //BASEOPEGL_RESOURCEMANAGER_H
