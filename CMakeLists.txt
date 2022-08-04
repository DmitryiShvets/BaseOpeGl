cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME BaseOpeGl)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

#find_package( OpenGL REQUIRED )
include_directories( greko/include )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(greko)

add_executable(${PROJECT_NAME} test1.cpp
        src/Core/ShaderProgram.cpp
        src/Core/ShaderProgram.h
        src/Core/ResourceManager.cpp
        src/Core/ResourceManager.h
        src/stb_image.h
        src/Core/Texture2D.cpp
        src/Core/Texture2D.h
        src/Core/Sprite2D.cpp
        src/Core/Sprite2D.h
        src/Core/MultiTexture2D.cpp
        src/Core/MultiTexture2D.h
        src/Core/SubTexture2D.cpp
        src/Core/SubTexture2D.h
        src/Core/Object2D.cpp
        src/Core/Object2D.h
        src/Core/SpriteAnimator.cpp
        src/Core/SpriteAnimator.h
        src/Game/Game.cpp
        src/Game/Game.h
        src/Core/BufferObjects.cpp
        src/Core/BufferObjects.h
        src/Core/Render.cpp
        src/Core/Render.h
        src/Core/TextRender.cpp
        src/Core/TextRender.h
        src/Core/Font.cpp
        src/Core/Font.h
        src/Core/Button.cpp
        src/Core/Button.h
        src/Core/Event.h
        src/Core/Menu.cpp
        src/Core/Menu.h
        src/Core/Application.cpp
        src/Core/Application.h
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
        )

#target_link_libraries(${PROJECT_NAME} glfw glm libopengl32.a glew32.lib freetype.lib )
target_link_libraries(${PROJECT_NAME} glfw glm libGL.so libGLEW.so libfreetype.so greko)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)