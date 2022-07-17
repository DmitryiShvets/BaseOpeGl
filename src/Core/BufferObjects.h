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

    void init(const void *data, const unsigned int size);

    void bind() const;

    void unbind() const;

    ~EBO();

    EBO(const EBO &) = delete;

    EBO &operator=(const EBO &) = delete;

    EBO(EBO &&ebo) noexcept;

    EBO &operator=(EBO &&ebo) noexcept;

private:
    GLuint mEBO;
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

    void addBuffer(const VBO &buffer, const VBOLayout &layout);

    ~VAO();

    VAO(const VAO &) = delete;

    VAO &operator=(const VAO &) = delete;

    VAO(VAO &&vao) noexcept;

    VAO &operator=(VAO &&vao) noexcept;

private:
    GLuint mVAO;
    unsigned int mBuffersCount = 0;
};


#endif //BASEOPEGL_BUFFEROBJECTS_H
