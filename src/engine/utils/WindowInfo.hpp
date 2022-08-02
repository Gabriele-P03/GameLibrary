/**
 * This class offers some static info about window:
 * 
 * Size
 * Frame
 */ 

#include <GLFW/glfw3.h>
#include "WindowSize.hpp"

namespace jpl{

    //They contains width and height of the window as it was maximized
    extern int MAX_WINDOW_W, MAX_WINDOW_H;


    /**
     * Callback for resizing window. This function is passed to GLFW#glfwSetWindowSizeCallback()
     * @param window
     * @param width
     * @param height
     */ 
    void window_size_callback(GLFWwindow* window, int width, int height);


    /**
     * Window size is in screen coordinates, not pixels.
     * glViewport() is a pixel-based OpenGl call, then we need to pass pixels as framebuffer size
     * This method is passed to GLFW#glfwSetFramebufferSizeCallback()
     * @param window
     * @param width
     * @param height
     */
    void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
}