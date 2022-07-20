//
// Created by dmirty on 20.07.2022.
//

#include "Button.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Render.h"

Button::Button(const glm::vec2 &position, const glm::vec2 &size) : mPos(position), mSize(size) {
    const GLfloat vertex[] = {
            //x(s)  y(t)
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
    };
    // GLuint menuVAO, menuVerVBO;
//    VBO menuVBO;
//    VAO menuVAO;
    //  glGenVertexArrays(1, &menuVAO);
    mVAO.bind();
    //  glBindVertexArray(menuVAO);

    //glGenBuffers(1, &menuVerVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, menuVerVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(menuVBO), &menuVBO, GL_STATIC_DRAW);
    mVBO.init(vertex, 2 * 6 * sizeof(GLfloat));

    VBOLayout menuVBOLayout;
    menuVBOLayout.addLayoutElement(2, GL_FLOAT, GL_FALSE);

    mVAO.addBuffer(mVBO, menuVBOLayout, 6);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


    mVBO.unbind();
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    mVAO.unbind();
    //  glBindVertexArray(0);

    //  glm::vec2 pos(10.0f, 800 - 50);
    //  glm::vec2 pos1(10.0f, 600 - 100);
    //  glm::vec2 size(100.0f, 30.0f);

    // auto &program = game.resourceManager.getProgram("defaultControl");

    program->use();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
    program->setUniform("projectionMatrix", projection);
    program->setUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
    program->unbind();

}

void Button::render() {
    //auto &program = game.resourceManager.getProgram("defaultControl");

    program->use();
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(mPos, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 * mSize.x, 0.5 * mSize.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5 * mSize.x, -0.5 * mSize.y, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(mSize, 1.0f));


    program->setUniform("modelMatrix", modelMatrix);

    Renderer::draw(mVAO);
    //  menuVAO.bind();
    // glBindVertexArray(menuVAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // menuVAO.unbind();
    //  glBindVertexArray(0);
    program->unbind();
}
