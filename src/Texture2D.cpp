//
// Created by Dmitry on 13.06.2022.
//
#include <stdexcept>
#include "Texture2D.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "stb_image.h"

Texture2D::Texture2D() {}

Texture2D::Texture2D(const char *path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(path, &width, &height, &channel, 0);
    if (!image)throw std::invalid_argument(path);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    switch (channel) {
        case 4:
            format = GL_RGBA;
            break;
        case 3:
            format = GL_RGB;
            break;
        default:
            format = GL_RGBA;
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    std::cout << "Texture" << path << " created"<< std::endl;
}

Texture2D::~Texture2D() {
    std::cout << "Texture " << " deleted"<< std::endl;
    glDeleteTextures(1, &textureID);
    textureID = 0;
}

Texture2D &Texture2D::operator=(Texture2D &&texture) noexcept {
    if (this != &texture) {
        glDeleteProgram(textureID);
        textureID = texture.textureID;
        format = texture.format;
        width = texture.width;
        height = texture.height;
        channel = texture.channel;

        texture.textureID = 0;

    }
    return *this;
}

Texture2D::Texture2D(Texture2D &&texture) noexcept {
    textureID = texture.textureID;
    format = texture.format;
    width = texture.width;
    height = texture.height;
    channel = texture.channel;

    texture.textureID = 0;
}

void Texture2D::bind() {
    if (textureID != 0) glBindTexture(GL_TEXTURE_2D, textureID);
    else std::cerr << "Texture not init";
}
