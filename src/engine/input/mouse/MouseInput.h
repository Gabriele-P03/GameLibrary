/**
 * Mouse Input Functions
 */ 

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <GLFW/glfw3.h>
#include "../../utils/WindowSize.hpp"


namespace jpl{

    inline int getButtonState(int button){
        return glfwGetMouseButton(glfwGetCurrentContext(), button);
    }
    
    inline bool isButtonPressed(int button){
        return getButtonState(button) == GLFW_PRESS;
    }

    inline bool isButtonReleased(int button){
        return getButtonState(button) == GLFW_RELEASE;
    }

    inline void getMousePosition(double *x, double *y){
        glfwGetCursorPos(glfwGetCurrentContext(), x, y);

        *y = (double)(jpl::WindowSize::INSTANCE.h - (int)(*y));
    }

    inline double getXPos(){
        double *x = new double;
        getMousePosition(x, new double);
        return *x;
    }

    inline double getYPos(){
        double *y = new double;
        getMousePosition(new double, y);
        return *y;
    }


    extern double xScrollOffset, yScrollOffset, xMouseOffset, yMouseOffset;
    extern int mouse_button, mouse_action, mouse_mods;

    extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    /**
     * GLFW doesn't provide static method about retrieving mouse position, then
     * in order to get it, you need to set a mouse position callback (as you done with error callback).
     * 
     * Call glfwSetMouseCallback() giving this name function. Once you need scroll amount, 
     * get it via getYOff() or getXOff(). You should always get scroll via getYOff()
     * 
     * Once call one of them, relative variable will be set as 0
     */ 
    extern void cursor_pos_callback(GLFWwindow* window, double xoffset, double yoffset);


    /**
     * GLFW doesn't provide static method about retrieving mouse scrolling then
     * in order to get it, you need to set a scroll callback (as you done with error callback).
     * 
     * Call glfwSetScrollCallback() giving this name function. Once you need scroll amount, 
     * get it via getYOff() or getXOff(). You should always get scroll via getYOff()
     * 
     * Once call one of them, relative variable will be set as 0
     */ 
    extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


}
#endif