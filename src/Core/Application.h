//
// Created by Dmitry on 24.07.2022.
//

#ifndef BASEOPEGL_APPLICATION_H
#define BASEOPEGL_APPLICATION_H

#include <string>

#define GLEW_STATIC

#include "GL/glew.h"


#include "GLFW/glfw3.h"

#include "ResourceManager.h"
#include "../Game/Game.h"


class Application {
public:
    static Application &getInstance();

    void init();

    void start();

    void close();

    ~Application();

    Application() = delete;

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;


private:
    Application(std::string name, int width, int height);

    std::string name;
    int width;
    int height;

    GLFWwindow *window = nullptr;
    ResourceManager *resourceManager = nullptr;
    Game *game = nullptr;

};


#endif //BASEOPEGL_APPLICATION_H
