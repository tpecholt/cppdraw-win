# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

add_library(imgui STATIC
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        misc/cpp/imgui_stdlib.cpp
        )

target_link_libraries(imgui
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        )

target_include_directories(imgui
PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
PRIVATE
        ${GLFW_INCLUDE_DIR}
        )
