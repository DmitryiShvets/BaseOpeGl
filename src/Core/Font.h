//
// Created by dmirty on 20.07.2022.
//

#ifndef BASEOPEGL_FONT_H
#define BASEOPEGL_FONT_H

#include <string>
#include "BufferObjects.h"
#include <map>
#include <glm/mat4x4.hpp>

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font {
public:
    Font(const std::string &font_ttf);

    ~Font();

    Font() = delete;

    Font(Font &) = delete;

    Font &operator=(const Font &) = delete;

    Font &operator=(Font &&other) noexcept;

    Font(Font &&other) noexcept;


    VAO mVAO;
    VBO mVBO;
    std::map<wchar_t, Character> mCharacters;
};

#endif //BASEOPEGL_FONT_H
