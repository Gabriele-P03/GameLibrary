#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <GLFW/glfw3.h>

namespace jpl{

    inline int getStateKey(int key){
        return glfwGetKey(glfwGetCurrentContext(), key);
    }

    inline bool isKeyPressed(int key){
        return getStateKey(key) == GLFW_PRESS;
    }

    inline bool isKeyReleased(int key){
        return getStateKey(key) == GLFW_RELEASE;
    }

    inline int getKeyScancode(int key){
        return glfwGetKeyScancode(key);
    }

    extern int key_buffer, scancode_buffer, action_buffer, mods_buffer;

    /**
     * This function is the keyboard callback
     * It is set as in the initializeLibrary()
     * 
     * You should never call this method again
     * 
     * This callback is used to save every key pressed into a char buffer var.
     */ 
    extern void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


    extern unsigned int codepoint;
    
    extern void character_callback(GLFWwindow* window, unsigned int codepoint);

}

#endif