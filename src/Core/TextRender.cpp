//
// Created by dmirty on 18.07.2022.
//

#include "TextRender.h"

#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
//#include <wchar.h>




// render line of text
// -------------------
void TextRenderer::draw(ShaderProgram *shader, std::string text, float x, float y, float scale, glm::vec3 color) {

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // activate corresponding render state
    shader->use();
    shader->setUniform("textColor", color);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));

    shader->setUniform("projection", projection);
    // glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    mVAO.bind();
    // glBindVertexArray(mVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                {xpos,     ypos + h, 0.0f, 0.0f},
                {xpos,     ypos,     0.0f, 1.0f},
                {xpos + w, ypos,     1.0f, 1.0f},

                {xpos,     ypos + h, 0.0f, 0.0f},
                {xpos + w, ypos,     1.0f, 1.0f},
                {xpos + w, ypos + h, 1.0f, 0.0f}
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        mVBO.update(vertices, sizeof(vertices));
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),vertices);
        mVBO.unbind();
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) *
             scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    mVAO.unbind();
    // glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    shader->unbind();

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
}

void TextRenderer::init() {

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(EXIT_FAILURE);
    }

    // find path to font
    std::string font_name = "res/fonts/Antonio-Bold.ttf";
    if (font_name.empty()) {
        std::cerr << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        exit(EXIT_FAILURE);
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++) {
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
            Characters.insert(std::pair<char, Character>(c, character));
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
