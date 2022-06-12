//
// Created by Dmitry on 11.06.2022.
//

#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram(const char *vertexShader, const char *fragmentShader) {
    //std::cout << "Constructor ShaderProgram (" << this << ") called " << std::endl;
    GLuint hVertexSh;
    if (!createShader(vertexShader, GL_VERTEX_SHADER, hVertexSh)) return;

    GLuint hFragmentSh;
    if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, hFragmentSh)) {
        glDeleteShader(hVertexSh);
        return;
    }
    hProgram = glCreateProgram();
    glAttachShader(hProgram, hVertexSh);
    glAttachShader(hProgram, hFragmentSh);
    glLinkProgram(hProgram);
    // Check for linking errors
    GLint success;
    glGetProgramiv(hProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(hProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    } else {
        compiled = true;
    }
    glDeleteShader(hVertexSh);
    glDeleteShader(hFragmentSh);


}

bool ShaderProgram::createShader(const char *source, const GLenum type, GLuint &hShader) {
    hShader = glCreateShader(type);
    glShaderSource(hShader, 1, &source, nullptr);
    glCompileShader(hShader);
    // Check for compile time errors
    GLint success;
    glGetShaderiv(hShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(hShader, 512, nullptr, infoLog);
        GLType errType(type);
        std::cout << "ERROR::SHADER::" << errType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}


bool ShaderProgram::isCompiled() const {
    return compiled;
}

void ShaderProgram::use() {
    glUseProgram(hProgram);
}

ShaderProgram::~ShaderProgram() {
    // std::cout << "Destructor ShaderProgram (" << this << ") called " << std::endl;
    glDeleteProgram(hProgram);
}

ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) : ShaderProgram(vertexShader.c_str(),
                                                                                                                 fragmentShader.c_str()) {
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&program) noexcept {
    // std::cout << "Assignment-Move ShaderProgram (" << this << ") called " << std::endl;
    if (this != &program) {
        glDeleteProgram(hProgram);
        hProgram = program.hProgram;
        compiled = program.compiled;

        program.hProgram = 0;
        program.compiled = false;
    }
    return *this;
}

ShaderProgram::ShaderProgram(ShaderProgram &&program) noexcept {
    // std::cout << "Constructor-Move ShaderProgram (" << this << ") called " << std::endl;
    hProgram = program.hProgram;
    compiled = program.compiled;

    program.hProgram = 0;
    program.compiled = false;

}

ShaderProgram::ShaderProgram() {
    std::cout << "Constructor-Default ShaderProgram (" << this << ") called " << std::endl;
}

 GLuint &ShaderProgram::getProgram() {
    return hProgram;
}

std::ostream &operator<<(std::ostream &lhs, const GLType e) {
    switch (e.type) {
        case GL_VERTEX_SHADER:
            lhs << "GL_VERTEX_SHADER";
            break;
        case GL_FRAGMENT_SHADER:
            lhs << "GL_FRAGMENT_SHADER";
            break;
    }
    return lhs;
}

GLType::GLType(GLuint thatType) {
    type = thatType;
}
