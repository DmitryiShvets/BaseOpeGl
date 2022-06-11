#include <iostream>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

void window_size_callback(GLFWwindow *window, int width, int height);

int main() {
    // GLFWwindow* window;
    GLfloat wWindow = 800.0f;
    GLfloat hWindow = 600.0f;
    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    auto window = glfwCreateWindow(wWindow, hWindow, "GLFW", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glClear(GL_COLOR_BUFFER_BIT);


    glClearColor(0.1f, 0.1f, 0.9f, 0.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);


        glColor3f(0.8f, 0.8f, 0.4f);

        glRectf(-0.5f, -0.5f,  0.5f, 0.5f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    std::cout << glfwGetVersionString();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
    // и приложение после этого закроется
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void window_size_callback(GLFWwindow *window, int width, int height) {
    if (height == 0)height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspectRatio = (GLfloat) width / (GLfloat) height;

    if (width <= height) {
        glOrtho(-1, 1, -1 / aspectRatio, 1 / aspectRatio, 1.0f, -1.0f);
    } else {
        glOrtho(-1 * aspectRatio, 1 * aspectRatio, -1, 1, 1.0f, -1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

