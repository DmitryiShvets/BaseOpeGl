//
// Created by Dmitry on 23.07.2022.
//

#ifndef BASEOPEGL_MENU_H
#define BASEOPEGL_MENU_H

#include "Button.h"
#include "Event.h"

class Menu {
public:

    Core::Event<void> closeEventHandler;

    static Menu &getInstance();

    void render();

    ~Menu();

    Button btn1;
    Button btn2;
private:

    Menu(int width, int height);

    //Button btn1(L"Выйти", glm::vec2(10.0f, windowSize.y - 50), glm::vec2(100.0f, 30.0f));
    // Button btn2(L"Exit", glm::vec2(10.0f, windowSize.y - 100), glm::vec2(100.0f, 30.0f));
    int mWindowWidth;
    int mWindowHeight;

};


#endif //BASEOPEGL_MENU_H
