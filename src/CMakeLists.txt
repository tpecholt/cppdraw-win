project(test)

# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

#GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glfw/include)
set(GLFW_DEFINITIONS -DGLFW_INCLUDE_NONE)

#imgui
add_subdirectory(imgui)

# TEST
add_executable(test WIN32
       cppdraw/cppdraw.h
       cppdraw/cppdraw.cpp
       main.cpp
       test.cpp
)

target_link_libraries(test
        glfw
        imgui
        ${OPENGL_LIBRARIES}
        )

target_include_directories(test
PRIVATE
        cppdraw
        )

add_definitions(-D_CRT_SECURE_NO_WARNINGS)