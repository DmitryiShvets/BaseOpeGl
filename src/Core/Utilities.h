//
// Created by Dmitry on 27.07.2022.
//

#ifndef BASEOPEGL_UTILITIES_H
#define BASEOPEGL_UTILITIES_H




#include "EventSystem.h"
#include "EventManager.h"
#include "Application.h"

class CallbackManager {
public:
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

    CallbackManager() = delete;

    ~CallbackManager() = delete;
};
//bool BtnPressed(int x, int y, Sprite2D &sprite2D) {
//    auto xpos = sprite2D.position().x;
//    auto ypos = sprite2D.position().y;
//    return (x > xpos) && (x < xpos + sprite2D.size().x) && (y > ypos) && (y < ypos + sprite2D.size().y);
//}


#endif //BASEOPEGL_UTILITIES_H
