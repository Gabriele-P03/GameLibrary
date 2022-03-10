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

void getMousePosition(double *x, double *y){
    glfwGetCursorPos(glfwGetCurrentContext(), x, y);
}

double getXPos(){
    double *x = new double;
    getMousePosition(x, new double);
    return *x;
}

double getYPos(){
    double *y = new double;
    getMousePosition(new double, y);
    return *y;
}
