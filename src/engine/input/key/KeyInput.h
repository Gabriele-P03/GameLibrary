#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <GLFW/glfw3.h>

extern int key_buffer, scancode_buffer, action_buffer, mods_buffer;

namespace jpl{



extern int getStateKey(int key);

extern bool isKeyPressed(int key);

extern bool isKeyReleased(int key);

extern int getKeyScancode(int key);

/**
 * This function is the keyboard callback
 * It is set as in the initializeLibrary()
 * 
 * You should never call this method again
 * 
 * This callback is used to save every key pressed into a char buffer var.
 */ 
extern void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif