#include "KeyInput.h"

int getStateKey(int key){
    return glfwGetKey(glfwGetCurrentContext(), key);
}

bool isKeyPressed(int key){
    return getStateKey(key) == GLFW_PRESS;
}

bool isKeyReleased(int key){
    return getStateKey(key) == GLFW_RELEASE;
}

int getKeyScancode(int key){
    return glfwGetKeyScancode(key);
}

int key_buffer, scancode_buffer, action_buffer, mods_buffer;

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    key_buffer = key;
    scancode_buffer = scancode;
    action_buffer = action;
    mods_buffer = mods;
}