//
// Created by Dmitry on 24.07.2022.
//

#include "Application.h"


#include <iostream>

#include "Texture2D.h"
#include "BufferObjects.h"
#include "EventManager.h"
#include <utility>
#include <chrono>
#include "Render.h"

#include <ft2build.h>
#include FT_FREETYPE_H


void Application::init() {


    if (!glfwInit()) {
        std::cerr << "Could not init glfw" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    Renderer::setViewPort(0, 0, w, h);

    resourceManager = &ResourceManager::getInstance();
    resourceManager->init();

    game = &Game::getInstance();
    game->init();

    menu = &Menu::getInstance();
    menu->closeEventHandler += Core::EventHandler::Bind(&Application::close, this);

}

Application::Application(std::string name, int width, int height) : name(std::move(name)), width(width), height(height) {}

bool BtnPressed(int x, int y, Sprite2D &sprite2D) {
    auto xpos = sprite2D.position().x;
    auto ypos = sprite2D.position().y;
    return (x > xpos) && (x < xpos + sprite2D.size().x) && (y > ypos) && (y < ypos + sprite2D.size().y);
}


void Application::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, nowHeight;
        glfwGetWindowSize(window, &width, &nowHeight);
        MouseButtonPressedEvent e(button, xpos, nowHeight - ypos);
        getInstance().eventRoute(&e);
        if (BtnPressed(xpos, nowHeight - ypos, Game::getInstance().getSprite("defaultSprite")))
            std::cout << "sprite - clicked!!!" << std::endl;
        else std::cout << "click - x: " << xpos << " y: " << nowHeight - ypos << std::endl;

    }
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) getInstance().switchState();


}

Application &Application::getInstance() {
    static Application instance("Window", 800, 600);
    return instance;
}

void Application::start() {

///----------Picture---------------------------------------------------------

    GLfloat vertices[] = {
            //x   //y   //z  //R    //G   //B   //s   //t
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
    };

    VBO VBO2;
    EBO EBO2;
    VAO VAO2;

    VAO2.bind();
    VBO2.init(vertices, 8 * 4 * sizeof(GLfloat));

    VBOLayout VBO2Layout;
    VBO2Layout.addLayoutElement(3, GL_FLOAT, GL_FALSE);
    VBO2Layout.addLayoutElement(3, GL_FLOAT, GL_FALSE);
    VBO2Layout.addLayoutElement(2, GL_FLOAT, GL_FALSE);

    VAO2.addBuffer(VBO2, VBO2Layout, 6);
    VBO2.unbind();

    EBO2.init(indices, 3 * 2);

    VAO2.unbind();
    EBO2.unbind();

    Texture2D &texture = resourceManager->getTexture("default");
///-----------------------------------------------------------------------------------


////MENU
    //Menu menu(width, height);
/////

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    auto start = std::chrono::high_resolution_clock::now();

    Renderer::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        Renderer::clear();

        resourceManager->getProgram("default").use();
        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        Renderer::draw(VAO2, EBO2);

        texture.unbind();

        resourceManager->getProgram("default").unbind();


        auto end = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = end;


        game->update(delta);
        game->render();

        if (gWindowPaused) {
            menu->render();
        }

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

void Application::eventRoute(Event *e) {
    if (e->getType() == Event::EventType::MOUSE_BUTTON_PRESSED_EVENT) {
        EventManager::getInstance().publish(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, e);
    }
}

void Application::switchState() {
    gWindowPaused = !gWindowPaused;
}


Application::~Application() {
    menu->closeEventHandler -= Core::EventHandler::Bind(&Application::close, this);
}

