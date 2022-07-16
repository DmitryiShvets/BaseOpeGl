//
// Created by Dmitry on 15.07.2022.
//

#include "SubTexture2D.h"


SubTexture2D::SubTexture2D(const glm::vec2 &leftBottom, const glm::vec2 &rightTop) : leftBottom(leftBottom), rightTop(rightTop) {}

SubTexture2D::SubTexture2D() : leftBottom(0.0f), rightTop(1.0f) {}
