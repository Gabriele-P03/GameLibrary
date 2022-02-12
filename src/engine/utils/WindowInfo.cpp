#include "WindowInfo.hpp"


void jpl::window_size_callback(GLFWwindow* window, int width, int height){
    glfwSetWindowAspectRatio(window, width, height);
}

void jpl::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    jpl::WindowSize::INSTANCE.w = width;
    jpl::WindowSize::INSTANCE.h = height;
}