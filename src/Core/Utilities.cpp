//
// Created by Dmitry on 27.07.2022.
//

#include <iostream>
#include "Utilities.h"

void CallbackManager::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, nowHeight;
        glfwGetWindowSize(window, &width, &nowHeight);
        MouseButtonPressedEvent e(button, xpos, nowHeight - ypos);
        EventManager::eventRoute(&e);
//        if (BtnPressed(xpos, nowHeight - ypos, Game::getInstance().getSprite("defaultSprite")))
//            std::cout << "sprite - clicked!!!" << std::endl;
//        else std::cout << "click - x: " << xpos << " y: " << nowHeight - ypos << std::endl;

    }
}

void CallbackManager::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) Application::getInstance().switchState();


}

void CallbackManager::cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    int width, nowHeight;
    glfwGetWindowSize(window, &width, &nowHeight);
    MouseMovedEvent e(xpos,nowHeight- ypos);
   // std::cout << xpos << " " <<nowHeight- ypos<< "\n";
    EventManager::eventRoute(&e);
}
