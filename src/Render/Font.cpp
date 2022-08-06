//
// Created by dmirty on 20.07.2022.
//


#include "Font.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

Font::Font(const std::string &font_ttf) {
    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(EXIT_FAILURE);
    }

    // find path to font
    //  std::string font_name = "res/fonts/OpenSans-Bold.ttf";
    if (font_ttf.empty()) {
        std::cerr << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        exit(EXIT_FAILURE);
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_ttf.c_str(), 0, &face)) {
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        std::wstring text(
                L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЬЪЭЮЯабвгдеёжзийклмнопрстуфхцчшщыьъэюяABCDEFGHIJKLMNOPRRSTUVWXQZabcdefghijklmnoprstuvwxqz 123456789.,!№;%:?*()_+=-~`|\\/\"><");
        // load first 128 characters of ASCII set
        for (int i = 0; i < text.size(); i++) {
            wchar_t c = text[i];
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            mCharacters.insert(std::pair<wchar_t, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // GLuint VAO, VBO;

    //  glGenVertexArrays(1, &VAO);
    mVAO.bind();
    //glBindVertexArray(VAO);
    mVBO.init(NULL, sizeof(GLfloat) * 6 * 4);
    //    glGenBuffers(1, &VBO);
    //    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    VBOLayout VBOLayout;
    VBOLayout.addLayoutElement(4, GL_FLOAT, GL_FALSE);
    mVAO.addBuffer(mVBO, VBOLayout, 6);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    mVBO.unbind();
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    mVAO.unbind();
    //  glBindVertexArray(0);
}


Font::~Font() {
    mCharacters.clear();
}

Font &Font::operator=(Font &&other) noexcept {
    if (this != &other) {
        mVAO = std::move(other.mVAO);
        mVBO = std::move(other.mVBO);
        mCharacters = std::move(other.mCharacters);
    }
    return *this;
}

Font::Font(Font &&other) noexcept {
    mVAO = std::move(other.mVAO);
    mVBO = std::move(other.mVBO);
    mCharacters = std::move(other.mCharacters);
}
