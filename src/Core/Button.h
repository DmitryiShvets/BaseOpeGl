//
// Created by dmirty on 20.07.2022.
//

#ifndef BASEOPEGL_BUTTON_H
#define BASEOPEGL_BUTTON_H

#include "ResourceManager.h"
#include "../Render/BufferObjects.h"
#include <glm/vec2.hpp>
#include "Event.h"
#include "EventManager.h"
#include "Subscriber.h"

//class Menu;

class Button : public Subscriber, Object2D {
public:
    Button(const std::wstring &content, const glm::vec2 &position, const glm::vec2 &size);

    void render();

    Core::Event<void> onClick;

    void onMouseBtnPressed(int button, double x, double y);

    ~Button() override;

    void update(Event *e) override;

private:
    //   glm::vec2 mPos;
    //   glm::vec2 mSize;
    VAO *mVAO = &ResourceManager::getInstance().baseVAO;
    std::wstring mContent;
    ShaderProgram *program = &ResourceManager::getInstance().getProgram("defaultControl");
};


#endif //BASEOPEGL_BUTTON_H
