#pragma once

#include <cstdio>

#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>

static void initGLEW()
{
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return;
    }
}

float mx{}, my{};

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) return;
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    mx = (float)(xpos / width) - 0.5;
    my = -(float)(ypos / height) + 0.5;
    mx *= 2;
    my *= 2;
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static GLFWwindow* initGLFW(int width, int height, const char* title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window{ nullptr };

    /* Initialize the library */
    if (!glfwInit())
        return nullptr;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    return window;
}

static GLFWwindow* initialize(int width, int height, const char* title)
{
    GLFWwindow *window = initGLFW(width, height, title);
    initGLEW();
    return window;
}