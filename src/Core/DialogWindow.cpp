//
// Created by Dmitry on 07.08.2022.
//

#include "DialogWindow.h"

DialogWindow::DialogWindow(const glm::vec2 &position, const glm::vec2 &size) : btnNewGameWhite(L"Белые", glm::vec2(position.x + 170,  position.y + 170),
                                                                                               glm::vec2(150, 50)),
                                                                               btnNewGameBlack(L"Черные",
                                                                                               glm::vec2(position.x + 170,position.y + 100),
                                                                                               glm::vec2(150, 50)),
                                                                               background(position, size, glm::vec3(0.50f, 0.36f, 0.10f)) {
    btnNewGameWhite.setDisabled();
    btnNewGameBlack.setDisabled();

    btnNewGameWhite.onClick += Core::EventHandler::Bind([this] {
        mActive = false;
        btnNewGameWhite.setDisabled();
        btnNewGameBlack.setDisabled();
    });
    btnNewGameBlack.onClick += Core::EventHandler::Bind([this] {
        mActive = false;
        btnNewGameWhite.setDisabled();
        btnNewGameBlack.setDisabled();
    });

}

void DialogWindow::render() {
    if (mActive) {
        btnNewGameWhite.setEnabled();
        btnNewGameBlack.setEnabled();

        background.render();
        btnNewGameWhite.render();
        btnNewGameBlack.render();
    }
}

DialogWindow::~DialogWindow() {
    btnNewGameWhite.onClick -= Core::EventHandler::Bind([this] {
        mActive = false;
        btnNewGameWhite.setDisabled();
        btnNewGameBlack.setDisabled();
    });
    btnNewGameBlack.onClick -= Core::EventHandler::Bind([this] {
        mActive = false;
        btnNewGameWhite.setDisabled();
        btnNewGameBlack.setDisabled();
    });
}


