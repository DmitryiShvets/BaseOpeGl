cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME BaseOpeGl)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

#find_package( OpenGL REQUIRED )
#include_directories( ${OPENGL_INCLUDE_DIRS} )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(${PROJECT_NAME} test1.cpp src/ShaderProgram.cpp src/ShaderProgram.h src/ResourceManager.cpp src/ResourceManager.h src/stb_image.h src/Texture2D.cpp src/Texture2D.h src/Sprite2D.cpp src/Sprite2D.h src/MultiTexture2D.cpp src/MultiTexture2D.h src/SubTexture2D.cpp src/SubTexture2D.h src/Object2D.cpp src/Object2D.h src/SpriteAnimator.cpp src/SpriteAnimator.h)

target_link_libraries(${PROJECT_NAME} glfw glm libopengl32.a glew32.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)