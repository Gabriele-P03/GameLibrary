#include "MouseInput.h"

int getButtonState(int button){
    return glfwGetMouseButton(glfwGetCurrentContext(), button);
}
 
bool isButtonPressed(int button){
    return getButtonState(button) == GLFW_PRESS;
}

bool isButtonReleased(int button){
    return getButtonState(button) == GLFW_RELEASE;
}


