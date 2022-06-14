#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "src/stb_image.h"

int main() {

    int channel;
    int width;
    int height;
    const char *path = "image.png";
    auto data = stbi_load(path, &width, &height, &channel, 0);
    if (data) {

        std::cout <<   sizeof(data) << " ";

    }


    return 0;
}


