/**
 * Mouse Input Functions
 */ 

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <GLFW/glfw3.h>




namespace jpl{

    extern double xScrollOffset, yScrollOffset, xMouseOffset, yMouseOffset;

/**
* Return if the given button is pressed
*/ 
bool isButtonPressed(int button);

/**
* Return if the given button is released
*/ 
bool isButtonReleased(int button);

/**
* Return the state of the given button
* 
* @return GLFW_PRESS if pressed otherwise GLFW_RELEASE
*/ 
int getButtonState(int button);

/**
 * Stores, inside parameters, position of the mouse pointer
 * @param x
 * @param y
 */ 
void getMousePosition(double *x, double *y);

/**
* @return x position of the mouse
*/ 
double getXPos();

/**
* @return current y position of the mouse
*/ 
double getYPos();

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
}
#endif