//
// Created by dmirty on 18.07.2022.
//

#ifndef BASEOPEGL_TEXTRENDER_H
#define BASEOPEGL_TEXTRENDER_H


#include "../Core/ResourceManager.h"


class TextRenderer {
public:
    static void draw(const std::wstring &text, float x, float y, float scale,float interval, glm::vec3 color, ShaderProgram *shader = &ResourceManager::getInstance().getProgram(
            "defaultText"), Font *font = &ResourceManager::getInstance().getFont("Open-Sans"));

};


#endif //BASEOPEGL_TEXTRENDER_H
