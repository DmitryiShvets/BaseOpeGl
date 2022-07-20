#include <iostream>

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <cmath>

#include "src/Core/Texture2D.h"
#include "src/Core/BufferObjects.h"
#include "src/Core/TextRender.h"
#include <glm/vec2.hpp>
#include <chrono>
#include "src/Game/Game.h"
#include "src/Core/Render.h"
#include "glm/gtc/matrix_transform.hpp"
#include "src/Core/Button.h"

#include <ft2build.h>
#include FT_FREETYPE_H

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

// Window dimensions
glm::ivec2 windowSize(800, 600);

//Window State
bool gWindowPaused = false;

// The MAIN function, from here we start the application and run the game loop
int main() {

    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

    Game game(windowSize);
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(windowSize.x, windowSize.y, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    game.init();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    Renderer::setViewPort(0, 0, width, height);
    //glViewport(0, 0, width, height);

///----------Picture---------------------------------------------------------

    GLfloat vertices[] = {
            //x   //y   //z  //R    //G   //B   //s   //t
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
    };

//    GLuint VBO1, VAO1, EBO1;
//
//
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glGenVertexArrays(1, &VAO1);
//    glBindVertexArray(VAO1);
//
//    glGenBuffers(1, &VBO1);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // Position attribute
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
//    // Color attribute
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
//    // TexCoord attribute
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glGenBuffers(1, &EBO1);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glBindVertexArray(0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    VBO VBO2;
    EBO EBO2;
    VAO VAO2;

    VAO2.bind();
    VBO2.init(vertices, 8 * 4 * sizeof(GLfloat));

    VBOLayout VBO2Layout;
    VBO2Layout.addLayoutElement(3, GL_FLOAT, GL_FALSE);
    VBO2Layout.addLayoutElement(3, GL_FLOAT, GL_FALSE);
    VBO2Layout.addLayoutElement(2, GL_FLOAT, GL_FALSE);

    VAO2.addBuffer(VBO2, VBO2Layout, 6);
    VBO2.unbind();

    EBO2.init(indices, 3 * 2);

    VAO2.unbind();
    EBO2.unbind();

    Texture2D &texture = game.resourceManager.getTexture("default");
///-----------------------------------------------------------------------------------


////MENU
    Button btn1(glm::vec2(10.0f, windowSize.y - 50), glm::vec2(100.0f, 30.0f));
    Button btn2(glm::vec2(10.0f, windowSize.y - 100), glm::vec2(100.0f, 30.0f));

/////
    // Uncommenting this call will result in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    auto start = std::chrono::high_resolution_clock::now();

    Renderer::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        Renderer::clear();
        //glClear(GL_COLOR_BUFFER_BIT);


        game.resourceManager.getProgram("default").use();
        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        Renderer::draw(VAO2, EBO2);
        // VAO2.bind();
        // glBindVertexArray(VAO1);
        //  glDrawArrays(GL_TRIANGLES, 0, 6);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // VAO2.unbind();
        //glBindVertexArray(0);

        texture.unbind();
        //glBindTexture(GL_TEXTURE_2D, 0);
        game.resourceManager.getProgram("default").unbind();
//        glUseProgram(0);

        auto end = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = end;


        game.update(delta);
        game.render();

        if (gWindowPaused) {

            btn1.render();
            btn2.render();

            TextRenderer::draw(L"привет habr. Я тут статью написал. Она о freetype и opengl.\n"
                               "С помощью freetype можно выводить текст.\n"
                               "А с помощью моего кода, можно вывести несколько строк в одной текстуре", 45.0f,
                               windowSize.y - 45, 0.4f, 20.0f, glm::vec3(1.0f, 0.8f, 0.2f));

        }



        // Swap the screen buffers
        glfwSwapBuffers(window);

        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    // Properly de-allocate all resources once they've outlived their purpose
    //   glDeleteVertexArrays(1, &VAO1);
    //  glDeleteBuffers(1, &VBO1);
    //   glDeleteBuffers(1, &EBO1);
    // glDeleteTextures(1, &texture);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    //   resourceManager.Destroy();
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        gWindowPaused = !gWindowPaused;

}

bool BtnPressed(int x, int y, Sprite2D &sprite2D) {
    auto xpos = sprite2D.position().x;
    auto ypos = sprite2D.position().y;
    return (x > xpos) && (x < xpos + sprite2D.size().x) && (y > ypos) && (y < ypos + sprite2D.size().y);
}


bool clicked(double x, double y, glm::ivec2 pos, glm::ivec2 size) {
    return (x > pos.x) && (x < pos.x + size.x) && (y > pos.y) && (y < pos.y + size.y);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        if (gWindowPaused &&
            clicked(xpos, height - ypos, glm::ivec2(10.0f, windowSize.y - 50), glm::ivec2(100.0f, 30.0f)))
            glfwSetWindowShouldClose(window, GL_TRUE);
        if (BtnPressed(xpos, height - ypos, ResourceManager::getInstance().getSprite("defaultSprite")))
            std::cout << "sprite - clicked!!!" << std::endl;
        else std::cout << "click - x: " << xpos << " y: " << height - ypos << std::endl;

    }
}

void draw_menu() {
    GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top Left
    };
}