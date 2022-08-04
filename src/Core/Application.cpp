//
// Created by Dmitry on 24.07.2022.
//

#include "Application.h"
//#include "glm/gtc/matrix_transform.hpp"

#include "greko.h"
#include <iostream>
#include <utility>
#include <chrono>

#include "EventManager.h"
#include "Render.h"
#include "Utilities.h"

#include <ft2build.h>
#include FT_FREETYPE_H

Application::Application(std::string name, int width, int height) : name(std::move(name)), width(width),
                                                                    height(height) {}

Application &Application::getInstance() {
    static Application instance("Window", 800, 800);
    return instance;
}

void Application::init() {


    if (!glfwInit()) {
        std::cerr << "Could not init glfw" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//    glfwWindowHint(GLFW_SAMPLES, 4);
//    glEnable(GL_MULTISAMPLE);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    if (!window) {
        std::cerr << "Could not CreateWindow" << std::endl;
        exit(EXIT_FAILURE);
    }


    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW failed..." << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, CallbackManager::key_callback);
    glfwSetMouseButtonCallback(window, CallbackManager::mouse_button_callback);
    glfwSetCursorPosCallback(window, CallbackManager::cursor_position_callback);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    Renderer::setViewPort(0, 0, w, h);

    resourceManager = &ResourceManager::getInstance();
    resourceManager->init();

    game = &Game::getInstance();
    game->closeEventHandler += Core::EventHandler::Bind(&Application::close, this);
    game->init();


}

void Application::start() {

///----------Picture---------------------------------------------------------


    double lastTime = glfwGetTime();
    int nbFrames = 0;

    auto start = std::chrono::high_resolution_clock::now();

    Renderer::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//
//    Greko greko;
//    greko.init(WHITE);
//
//    greko.MakeMovePlayer("e2e4");
//    std::cout << "Компьютер сделал ход : " << greko.MakeMoveEngine() << std::endl;
//
//    greko.MakeMovePlayer("d2d4");
//    std::cout << "Компьютер сделал ход : " << greko.MakeMoveEngine() << std::endl;


    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        Renderer::clear();


        auto end = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = end;



        game->update(delta);
        game->render();



        // Swap the screen buffers
        glfwSwapBuffers(window);

        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    game->destroy();
    resourceManager->destroy();
    glfwTerminate();
}

void Application::close() {
    glfwSetWindowShouldClose(window, GL_TRUE);
}

Application::~Application() {
    game->closeEventHandler -= Core::EventHandler::Bind(&Application::close, this);

}

