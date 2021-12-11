/**
 * Mouse Input Functions
 */ 

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <GLFW/glfw3.h>

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
* Return current x position of the mouse
*/ 
int getXPos();

/**
* Return current y position of the mouse
*/ 
int getYPos();

/**
 * GLFW doesn't provide static method about retrieving position or state of buttons, then
 * in order to get scroll of wheel you need to set a scroll callback (as you done with error callback).
 * 
 * Call glfwSetScrollCallback() giving this name function. Once you need scroll amount, 
 * get it via getYOff() or getXOff(). You should always get scroll via getYOff()
 * 
 * Once call one of them, relative variable will be set as 0
 */ 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
double getXOff();
double getYOff();


#endif