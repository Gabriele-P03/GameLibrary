#include "MouseInput.h"

int jpl::getButtonState(int button){
    return glfwGetMouseButton(glfwGetCurrentContext(), button);
}
 
bool jpl::isButtonPressed(int button){
    return jpl::getButtonState(button) == GLFW_PRESS;
}

bool jpl::isButtonReleased(int button){
    return jpl::getButtonState(button) == GLFW_RELEASE;
}

void jpl::getMousePosition(double *x, double *y){
    glfwGetCursorPos(glfwGetCurrentContext(), x, y);
}

double jpl::getXPos(){
    double *x = new double;
    jpl::getMousePosition(x, new double);
    return *x;
}

double jpl::getYPos(){
    double *y = new double;
    jpl::getMousePosition(new double, y);
    return *y;
}
