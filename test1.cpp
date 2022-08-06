#include "src/Application.h"

int main() {

    Application &app = Application::getInstance();
    app.init();
    app.start();

    return 0;
}


