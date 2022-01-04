/**
 * This is only an example file for explaining the use of WindowInfo.hpp
 * If the methods defined below do what you're looking for, you could use them without any problems.
 * Otherwise, you should create you own cpp including WindowInfo.hpp and define them 
 */ 

#include "WindowInfo.hpp"

void jpl::window_size_callback(GLFWwindow* window, int width, int height){
    glfwSetWindowAspectRatio(window, width, height);
}

void jpl::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    
}