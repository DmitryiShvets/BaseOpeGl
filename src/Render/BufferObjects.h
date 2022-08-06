//
// Created by Dmitry on 17.07.2022.
//

#ifndef BASEOPEGL_BUFFEROBJECTS_H
#define BASEOPEGL_BUFFEROBJECTS_H

#include <GL/glew.h>
#include <vector>

class VBO {
public:
    VBO();

    void init(const void *data, const unsigned int size);

    void update(const void *data, const unsigned int size) const;

    void bind() const;

    void unbind() const;

    ~VBO();

    VBO(const VBO &) = delete;

    VBO &operator=(const VBO &) = delete;

    VBO(VBO &&vbo) noexcept;

    VBO &operator=(VBO &&vbo) noexcept;

private:
    GLuint mVBO;
};


class EBO {
public:
    EBO();

    void init(const void *data, const unsigned int count);

    void bind() const;

    void unbind() const;

    unsigned int count() const;

    ~EBO();

    EBO(const EBO &) = delete;

    EBO &operator=(const EBO &) = delete;

    EBO(EBO &&ebo) noexcept;

    EBO &operator=(EBO &&ebo) noexcept;

private:
    GLuint mEBO;

    unsigned int mCount;
};

struct VBOLayoutElements {
    GLint count;
    GLenum type;
    GLboolean normalized;
    unsigned long long size;
};

class VBOLayout {
public:
    VBOLayout();

    ~VBOLayout();

    void addLayoutElement(GLint count, GLenum type, GLboolean normalized);

    unsigned int getStride() const;

    const std::vector<VBOLayoutElements> &getLayoutElements() const;

private:
    unsigned int mStride;
    std::vector<VBOLayoutElements> mVecLayoutElements;
};

class VAO {
public:
    VAO();

    void bind() const;

    void unbind() const;

    void addBuffer(const VBO &buffer, const VBOLayout &layout,const unsigned  int countVertex=0);

    unsigned int count() const;

    ~VAO();

    VAO(const VAO &) = delete;

    VAO &operator=(const VAO &) = delete;

    VAO(VAO &&vao) noexcept;

    VAO &operator=(VAO &&vao) noexcept;

private:
    GLuint mVAO;
    unsigned int mBuffersCount = 0;
    unsigned int mVertexCount = 0;
};

///---EXAMPLE------------
//    GLfloat vertices[] = {
//            //x   //y   //z  //R    //G   //B
//            0.0f, 0.0f,   // Top Right
//            0.0f, 1.0f,    // Bottom Right
//            1.0f, 1.0f,   // Bottom Left
//            1.0f, 0.0f  // Top Left
//    };
//
//    GLuint indices[] = {  // Note that we start from 0!
//            0, 1, 3,  // First Triangle
//            1, 2, 3   // Second Triangle
//    };
//
//    GLuint VBO1, VAO1, EBO1;
//
//
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glGenVertexArrays(1, &VAO1);
//    glBindVertexArray(VAO1);
//
//    glGenBuffers(1, &VBO1);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // Position attribute
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
//    // Color attribute
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
//    // TexCoord attribute
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glGenBuffers(1, &EBO1);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glBindVertexArray(0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


//
//VBO VBO2;
//EBO EBO2;
//VAO VAO2;
//
//VAO2.bind();
//VBO2.init(vertices, 8 * 4 * sizeof(GLfloat));
//
//VBOLayout VBO2Layout;
//VBO2Layout.addLayoutElement(3, GL_FLOAT, GL_FALSE);
//VBO2Layout.addLayoutElement(3, GL_FLOAT, GL_FALSE);
//VBO2Layout.addLayoutElement(2, GL_FLOAT, GL_FALSE);
//
//VAO2.addBuffer(VBO2, VBO2Layout, 6);
//VBO2.unbind();
//
//EBO2.init(indices, 3 * 2);
//
//VAO2.unbind();
//EBO2.unbind();

#endif //BASEOPEGL_BUFFEROBJECTS_H
