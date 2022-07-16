//
// Created by Dmitry on 15.06.2022.
//

#include "MultiTexture2D.h"
#include "SubTexture2D.h"
#include <iostream>

MultiTexture2D::MultiTexture2D(const char *path, const std::vector<size_t> &subTexNames, unsigned int subTexWidth, unsigned int subTexHeight) : Texture2D(
        path) {
    unsigned int offsetX = 0;
    unsigned int offsetY = 0;
    for (const auto &item: subTexNames) {
        glm::vec2 leftBottom(static_cast<float>(offsetX) / mWidth, static_cast<float>(offsetY) / mHeight);
        glm::vec2 rightTop(static_cast<float>(offsetX + subTexWidth) / mWidth, static_cast<float>(offsetY + subTexHeight) / mHeight);
        addSubTexture(item, leftBottom, rightTop);

        offsetX += subTexWidth;
        if (offsetX >= mWidth) {
            offsetX = 0;
            offsetY += subTexHeight;
        }
    }
  //  std::cout << "Texture MULTI (" << this << ") " << path << " created" << std::endl;
}

void MultiTexture2D::addSubTexture(const size_t &subTexName, const glm::vec2 &leftBottom, const glm::vec2 &rightTop) {
    mSubTexturesMap.emplace(subTexName, SubTexture2D(leftBottom, rightTop));
}

const SubTexture2D &MultiTexture2D::getSubTexture(const size_t &subTexName) {

    auto it = mSubTexturesMap.find(subTexName);
    if (it != mSubTexturesMap.end()) {
        return it->second;
    }
    const static SubTexture2D defaultSubTexture;
    return defaultSubTexture;
}


MultiTexture2D::MultiTexture2D(MultiTexture2D &&texture2D) noexcept: Texture2D(std::move(texture2D)) {
  //  std::cout << "Assignment-Move MultiTexture2D (" << this << ") called " << std::endl;
    mSubTexturesMap = texture2D.mSubTexturesMap;

    texture2D.mSubTexturesMap.clear();
}

MultiTexture2D &MultiTexture2D::operator=(MultiTexture2D &&texture2D) noexcept {
   // std::cout << "Constructor-Move MultiTexture2D (" << this << ") called " << std::endl;
    if (this != &texture2D) {

        mSubTexturesMap = texture2D.mSubTexturesMap;

        texture2D.mSubTexturesMap.clear();
        Texture2D::operator=(std::move(texture2D));
    }
    return *this;
}

MultiTexture2D::~MultiTexture2D() {
   // std::cout << "Texture MULTI (" << this << ")" << " deleted" << std::endl;
    mSubTexturesMap.clear();
}


