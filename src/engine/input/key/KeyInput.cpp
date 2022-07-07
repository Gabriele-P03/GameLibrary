#include "KeyInput.h"

int jpl::getStateKey(int key){
    return glfwGetKey(glfwGetCurrentContext(), key);
}

bool jpl::isKeyPressed(int key){
    return jpl::getStateKey(key) == GLFW_PRESS;
}

bool jpl::isKeyReleased(int key){
    return jpl::getStateKey(key) == GLFW_RELEASE;
}

int jpl::getKeyScancode(int key){
    return glfwGetKeyScancode(key);
}

int key_buffer, scancode_buffer, action_buffer, mods_buffer;

void jpl::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    key_buffer = key;
    scancode_buffer = scancode;
    action_buffer = action;
    mods_buffer = mods;
}