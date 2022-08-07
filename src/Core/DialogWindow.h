//
// Created by Dmitry on 07.08.2022.
//

#ifndef BASEOPEGL_DIALOGWINDOW_H
#define BASEOPEGL_DIALOGWINDOW_H

#include "Button.h"
#include "Event.h"
#include "Label.h"

class DialogWindow {
public:
    void render();

    ~DialogWindow();

    DialogWindow(const glm::vec2 &position, const glm::vec2 &size);

    Button btnNewGameWhite;

    Button btnNewGameBlack;

    inline void show() { mActive = true; }


private:
    Label background;
    bool mActive = false;

};


#endif //BASEOPEGL_DIALOGWINDOW_H
