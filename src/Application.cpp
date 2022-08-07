//
// Created by Dmitry on 24.07.2022.
//

#include "Application.h"

#include <iostream>
#include <utility>
#include <chrono>

#include "Core/EventManager.h"
#include "Render/Render.h"
#include "Core/Utilities.h"

#include <ft2build.h>
#include FT_FREETYPE_H


Application::Application(std::string name, int width, int height) : name(std::move(name)), width(width),
                                                                    height(height) {}

Application &Application::getInstance() {
    static Application instance("Window", 900, 900);
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

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);


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
    game->init();

    menu = &Menu::getInstance();
    menu->dialogWindow.btnNewGameWhite.onClick += Core::EventHandler::Bind([this] {
        label->setDisabled();
        game->newGame(0);
        mGamePaused = false;
        mGamePlay = true;
    });

    menu->dialogWindow.btnNewGameBlack.onClick += Core::EventHandler::Bind([this] {
        label->setDisabled();
        game->newGame(1);
        mGamePaused = false;
        mGamePlay = true;
    });
    menu->btn2.onClick += Core::EventHandler::Bind([this] { if (mGamePaused)close(); });


    EventManager::getInstance().subscribe(Event::EventType::KEY_PRESSED_EVENT, this);
    EventManager::getInstance().subscribe(Event::EventType::GAME_END_EVENT, this);

    label = new Label(glm::vec2(300, 700), glm::vec2(300, 100), glm::vec3(0.2f, 0.3f, 0.3f));

}

void Application::start() {

///----------Picture---------------------------------------------------------


    double lastTime = glfwGetTime();
    int nbFrames = 0;

    auto start = std::chrono::high_resolution_clock::now();

    Renderer::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Label label(glm::vec2(50, 0), glm::vec2(100, 50), glm::vec3(1.0f, 1.0f, 1.0f), L"S");
    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        Renderer::clear();


        auto end = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = end;


        if (mGamePlay) {
            game->update(delta);
            game->render();
        }

        if (mGamePaused) menu->render();

        label->render();


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


    menu->dialogWindow.btnNewGameWhite.onClick -= Core::EventHandler::Bind([this] {
        label->setDisabled();
        game->newGame(0);
        mGamePaused = false;
        mGamePlay = true;
    });

    menu->dialogWindow.btnNewGameBlack.onClick -= Core::EventHandler::Bind([this] {
        label->setDisabled();
        game->newGame(1);
        mGamePaused = false;
        mGamePlay = true;
    });
    menu->btn2.onClick -= Core::EventHandler::Bind([this] { if (mGamePaused)close(); });


    EventManager::getInstance().unsubscribe(Event::EventType::KEY_PRESSED_EVENT, this);
    EventManager::getInstance().unsubscribe(Event::EventType::GAME_END_EVENT, this);

    delete label;
}

void Application::update(Event *e) {
    if (e->getType() == Event::EventType::KEY_PRESSED_EVENT) {
        auto *event = dynamic_cast<KeyPressedEvent * >(e);
        if (event->key == 257) {
            mGamePaused = !mGamePaused;
            GamePausedEvent ev(mGamePaused);
            EventManager::eventRoute(&ev);
        }

    }
    if (e->getType() == Event::EventType::GAME_END_EVENT) {
        auto *event = dynamic_cast<GameEndEvent * >(e);
        label->changeText(std::wstring(event->comment.begin(), event->comment.end()));
        label->setEnabled();
    }
}

