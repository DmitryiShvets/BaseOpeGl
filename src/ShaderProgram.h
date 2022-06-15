//
// Created by Dmitry on 11.06.2022.
//

#ifndef BASEOPEGL_SHADERPROGRAM_H
#define BASEOPEGL_SHADERPROGRAM_H

#include <GL/glew.h>
#include <sstream>
#include <string>
#include <glm/mat4x4.hpp>

class GLType {

public:
    GLuint type;

    explicit GLType(GLuint thatType);

    friend std::ostream &operator<<(std::ostream &lhs, const GLType e);

};


class ShaderProgram {


public:
    ShaderProgram(const char *vertexShader, const char *fragmentShader);

    ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);

    bool isCompiled() const;

    void use();

    GLuint &getUintProgram();

    void setUniform(const std::string &uniformName, const glm::mat4 &matrixValue);

    void setUniform(const std::string &uniformName, int value);

    void setUniform(const std::string &uniformName, const glm::vec4 &vec4Value);

    ~ShaderProgram();

    ShaderProgram() = delete;

    ShaderProgram(ShaderProgram &) = delete;

    ShaderProgram &operator=(const ShaderProgram &) = delete;

    ShaderProgram &operator=(ShaderProgram &&program) noexcept;

    ShaderProgram(ShaderProgram &&program) noexcept;


private:
    bool createShader(const char *source, const GLenum type, GLuint &hShader);

    bool compiled = false;

    GLuint hProgram = 0;


};


#endif //BASEOPEGL_SHADERPROGRAM_H
