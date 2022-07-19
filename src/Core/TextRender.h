//
// Created by dmirty on 18.07.2022.
//

#ifndef BASEOPEGL_TEXTRENDER_H
#define BASEOPEGL_TEXTRENDER_H


#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "BufferObjects.h"

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    void draw(ShaderProgram *shader, std::string text, float x, float y, float scale, glm::vec3 color);

    void init();

private:
    VAO mVAO;
    VBO mVBO;
    std::map<GLchar, Character> Characters;
};


#endif //BASEOPEGL_TEXTRENDER_H
