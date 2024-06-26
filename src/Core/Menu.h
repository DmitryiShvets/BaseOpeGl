//
// Created by Dmitry on 23.07.2022.
//

#ifndef BASEOPEGL_MENU_H
#define BASEOPEGL_MENU_H

#include "Button.h"
#include "Event.h"
#include "Label.h"
#include "DialogWindow.h"


class Menu {
public:

    static Menu &getInstance();

    void render();

    ~Menu();

    Button btn1;
    Button btn2;
    DialogWindow dialogWindow;

private:

    bool mActive = true;
    Label background;

    Menu(int width, int height);

    int mWindowWidth;
    int mWindowHeight;

};


#endif //BASEOPEGL_MENU_H
