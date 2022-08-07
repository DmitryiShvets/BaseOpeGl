//
// Created by Dmitry on 23.07.2022.
//

#include "Menu.h"

Menu::Menu(int width, int height) : mWindowWidth(width), mWindowHeight(height),
                                    btn1(L"Новая игра", glm::vec2(370.0f, height - 330), glm::vec2(150.0f, 50.0f)),
                                    btn2(L"Выйти", glm::vec2(370.0f, height - 400), glm::vec2(150.0f, 50.0f)),
                                    background(glm::vec2(200, 400), glm::vec2(500, 300), glm::vec3(0.50f, 0.36f, 0.10f)),
                                    dialogWindow(glm::vec2(200, 400), glm::vec2(500, 300)) {

    btn1.onClick += Core::EventHandler::Bind([this] {
        dialogWindow.show();
        btn1.setDisabled();
        btn2.setDisabled();
    });
    dialogWindow.btnNewGameWhite.onClick += Core::EventHandler::Bind([this] {
        btn1.setEnabled();
        btn2.setEnabled();
    });
    dialogWindow.btnNewGameBlack.onClick += Core::EventHandler::Bind([this] {
        btn1.setEnabled();
        btn2.setEnabled();
    });
}

void Menu::render() {

    background.render();
    btn1.render();
    btn2.render();

    dialogWindow.render();
}


Menu::~Menu() {
    btn1.onClick -= Core::EventHandler::Bind([this] {
        dialogWindow.show();
        btn1.setDisabled();
        btn2.setDisabled();
    });

    dialogWindow.btnNewGameWhite.onClick -= Core::EventHandler::Bind([this] {
        btn1.setEnabled();
        btn2.setEnabled();
    });
    dialogWindow.btnNewGameBlack.onClick -= Core::EventHandler::Bind([this] {
        btn1.setEnabled();
        btn2.setEnabled();
    });
}

Menu &Menu::getInstance() {
    static Menu instance(900, 900);
    return instance;
}


