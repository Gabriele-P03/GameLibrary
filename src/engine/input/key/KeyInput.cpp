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