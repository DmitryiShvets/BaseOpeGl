#include <iostream>

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <cmath>

#include "src/ShaderProgram.h"
#include "src/ResourceManager.h"
#include "src/Texture2D.h"
#include "src/Sprite2D.h"
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// Window dimensions
glm::ivec2 windowSize(800, 600);
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
//const GLchar *vertexShaderSource = "#version 330 core\n"
//                                   "layout (location = 0) in vec3 position;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//                                   "}\0";
//const GLchar *fragmentShaderSource = "#version 330 core \n out vec4 color; void main() { color = vec4(1.0f, 0.5f, 0.2f, 1.0f);}";

// The MAIN function, from here we start the application and run the game loop
int main() {

    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

    ResourceManager &resourceManager = ResourceManager::getInstance();
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

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
    resourceManager.Init();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);
    // if (!shaderProgram.isCompiled())return -1;




    GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    const char *path = "awesomeface.png";
    Texture2D &texture = resourceManager.getTexture("default");

    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y), -100.f, 100.f);
    //  Sprite2D sprite2D("defaultSprite", "defaultSprite", glm::vec2(10.0f, 10.0f), glm::vec2(100.0f, 100.0f), 0);
//    Sprite2D sprite2D(glm::vec2(10.0f, 10.0f), glm::vec2(100.0f, 100.0f), 0, &resourceManager.getTexture("defaultSprite"),
//                       &resourceManager.getProgram("defaultSprite"));
    Sprite2D sprite2D1( &resourceManager.getMultiTexture("defaultSprite"),
                       &resourceManager.getProgram("defaultSprite"), 2);
    resourceManager.getProgram("defaultSprite").use();
    resourceManager.getProgram("defaultSprite").setUniform("ourTexture", 0);
    resourceManager.getProgram("defaultSprite").setUniform("projectionMatrix", projectionMatrix);
    glUseProgram(0);


    // Uncommenting this call will result in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        resourceManager.getProgram("default").use();
        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);

       sprite2D1.render(glm::vec2(100.0f, 100.0f), glm::vec2(100.0f, 100.0f), -30, 4);


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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glDeleteTextures(1, &texture);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    resourceManager.Destroy();
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}