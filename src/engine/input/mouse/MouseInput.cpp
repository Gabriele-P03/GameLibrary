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

double jpl::xMouseOffset, jpl::yMouseOffset, jpl::xScrollOffset, jpl::yScrollOffset;

void jpl::cursor_pos_callback(GLFWwindow* window, double xoffset, double yoffset){
    jpl::xMouseOffset = xoffset;
    jpl::yMouseOffset = yoffset;
}

void jpl::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    jpl::xScrollOffset = xoffset;
    jpl::yScrollOffset = yoffset;
}
