//
// Created by Dmitry on 15.07.2022.
//

#ifndef BASEOPEGL_SUBTEXTURE2D_H
#define BASEOPEGL_SUBTEXTURE2D_H

#include <glm/vec2.hpp>

class SubTexture2D {
public:
    SubTexture2D(const glm::vec2 &leftBottom, const glm::vec2 &rightTop);

    SubTexture2D();

    glm::vec2 leftBottom;
    glm::vec2 rightTop;

};

#endif //BASEOPEGL_SUBTEXTURE2D_H
