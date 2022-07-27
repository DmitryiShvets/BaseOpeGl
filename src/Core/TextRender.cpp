//
// Created by dmirty on 18.07.2022.
//

#include "TextRender.h"
#include <GL/glew.h>

#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"


void TextRenderer::draw(const std::wstring &text, float xOrigin, float yOrigin, float scale, float interval, glm::vec3 color, ShaderProgram *shader, Font *font) {
    {

        auto x = xOrigin;
        auto y = yOrigin;

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
        font->mVAO.bind();
        // glBindVertexArray(mVAO);

        // iterate through all characters
        std::wstring::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) {
            Character ch = font->mCharacters[*c];

            if (*c == '\n') {
                y -= interval;
                x = xOrigin;
                continue;
            }

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
            font->mVBO.update(vertices, sizeof(vertices));
            // glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),vertices);
            font->mVBO.unbind();
            // glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels
            // (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        font->mVAO.unbind();
        // glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        shader->unbind();

        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }
}