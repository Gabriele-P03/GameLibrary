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

int jpl::key_buffer, jpl::scancode_buffer, jpl::action_buffer, jpl::mods_buffer;

void jpl::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    jpl::key_buffer = key;
    jpl::scancode_buffer = scancode;
    jpl::action_buffer = action;
    jpl::mods_buffer = mods;
}