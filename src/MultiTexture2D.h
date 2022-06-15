//
// Created by Dmitry on 15.06.2022.
//

#ifndef BASEOPEGL_MULTITEXTURE2D_H
#define BASEOPEGL_MULTITEXTURE2D_H

#include "Texture2D.h"
#include <glm/vec2.hpp>
#include <map>
#include <string>
#include <vector>

class SubTexture2D {
public:
    SubTexture2D(const glm::vec2 &leftBottom, const glm::vec2 &rightTop);

    SubTexture2D();

    glm::vec2 leftBottom;
    glm::vec2 rightTop;

};

class MultiTexture2D : public Texture2D {
public:
    MultiTexture2D(const char *path, const std::vector<std::string> &subTexNames, unsigned int subTexWidth = 0, unsigned int subTexHeight = 0);

    virtual ~MultiTexture2D();

    MultiTexture2D() = delete;

    MultiTexture2D(MultiTexture2D &) = delete;

    MultiTexture2D &operator=(const MultiTexture2D &) = delete;

    MultiTexture2D &operator=(MultiTexture2D &&texture2D) noexcept;

    MultiTexture2D(MultiTexture2D &&texture2D) noexcept;

    const SubTexture2D &getSubTexture(const std::string &subTexName);

private:

    void addSubTexture(const std::string &subTexName, const glm::vec2 &leftBottom, const glm::vec2 &rightTop);

    std::map<std::string, SubTexture2D> mSubTexturesMap;
};


#endif //BASEOPEGL_MULTITEXTURE2D_H
