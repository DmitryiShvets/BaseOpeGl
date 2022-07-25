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
#include "EventSystem.h"
#include "Menu.h"

class Application {
public:
    static Application &getInstance();

    void init();

    void start();

    void close();

    ~Application();

    Application() = delete;

    Application(const Application &) = delete;

private:
    Application(std::string name, int width, int height);

    Application &operator=(const Application &) = delete;

    ResourceManager *resourceManager = nullptr;

    Game *game = nullptr;

    Menu *menu = nullptr;
    // Window &window;
    std::string name;
    int width;
    int height;
    GLFWwindow *window = nullptr;

    bool gWindowPaused = false;

    void switchState();

    void eventRoute(Event *e);

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
};


#endif //BASEOPEGL_APPLICATION_H