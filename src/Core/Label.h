//
// Created by Dmitry on 06.08.2022.
//

#ifndef BASEOPEGL_LABEL_H
#define BASEOPEGL_LABEL_H

#include "ResourceManager.h"
#include <glm/vec2.hpp>


class Label : public Object2D {
public:
    Label(const glm::vec2 &position, const glm::vec2 &size, const glm::vec3 &color, std::wstring content = L"");

    Label() = delete;

    Label(Label &) = delete;

    Label &operator=(const Label &) = delete;

    Label &operator=(Label &&other) noexcept;

    void changeText(std::wstring text);

    inline void setEnabled() { mActive = true; }

    inline void setDisabled() {mActive = false; }

    Label(Label &&other) noexcept;

    void render();

    ~Label();

private:
    bool mActive = true;
    std::wstring mContent;
    glm::vec3 mColor;
    VAO *mVAO = &ResourceManager::getInstance().baseVAO;
    ShaderProgram *mProgram = &ResourceManager::getInstance().getProgram("default");
};


#endif //BASEOPEGL_LABEL_H
