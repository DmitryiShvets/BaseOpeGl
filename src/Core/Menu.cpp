//
// Created by Dmitry on 23.07.2022.
//

#include "Menu.h"


Menu::Menu(int width, int height) : mWindowWidth(width), mWindowHeight(height),
                                    btn1(L"Выйти", glm::vec2(10.0f, height - 50), glm::vec2(100.0f, 30.0f)),
                                    btn2(L"Exit", glm::vec2(10.0f, height - 100), glm::vec2(100.0f, 30.0f)) {
}

void Menu::render() {


    btn1.render();
    btn2.render();
}


Menu::~Menu() {
}

Menu &Menu::getInstance() {
    static Menu instance(900, 900);
    return instance;
}


