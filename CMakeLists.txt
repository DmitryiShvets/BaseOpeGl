cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME BaseOpeGl)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

#find_package( OpenGL REQUIRED )
include_directories(greko/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(greko)

add_executable(${PROJECT_NAME} test1.cpp
        src/Render/ShaderProgram.cpp
        src/Render/ShaderProgram.h
        src/Core/ResourceManager.cpp
        src/Core/ResourceManager.h
        src/stb_image.h
        src/Render/Texture2D.cpp
        src/Render/Texture2D.h
        src/Render/Sprite2D.cpp
        src/Render/Sprite2D.h
        src/Render/MultiTexture2D.cpp
        src/Render/MultiTexture2D.h
        src/Render/SubTexture2D.cpp
        src/Render/SubTexture2D.h
        src/Render/Object2D.cpp
        src/Render/Object2D.h
        src/Render/SpriteAnimator.cpp
        src/Render/SpriteAnimator.h
        src/Game/Game.cpp
        src/Game/Game.h
        src/Render/BufferObjects.cpp
        src/Render/BufferObjects.h
        src/Render/Render.cpp
        src/Render/Render.h
        src/Render/TextRender.cpp
        src/Render/TextRender.h
        src/Render/Font.cpp
        src/Render/Font.h
        src/Core/Button.cpp
        src/Core/Button.h
        src/Core/Event.h
        src/Core/Menu.cpp
        src/Core/Menu.h
        src/Application.cpp
        src/Application.h
        src/Core/EventSystem.h
        src/Core/Subscriber.h
        src/Core/EventManager.cpp
        src/Core/EventManager.h
        src/Game/SquareNode.cpp
        src/Game/SquareNode.h
        src/Core/Utilities.cpp
        src/Core/Utilities.h
        # greko/greko.cpp
        # greko/greko.h
        src/Game/Level.cpp
        src/Game/Level.h
        src/Game/Figure.cpp
        src/Game/Figure.h
        src/Core/Label.cpp
        src/Core/Label.h
        src/Core/DialogWindow.cpp
        src/Core/DialogWindow.h)

target_link_libraries(${PROJECT_NAME} glfw glm libopengl32.a glew32.lib freetype.lib greko)
#target_link_libraries(${PROJECT_NAME} glfw glm libGL.so libGLEW.so libfreetype.so greko)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)