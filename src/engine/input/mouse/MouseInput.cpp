#include "MouseInput.h"

double jpl::xMouseOffset, jpl::yMouseOffset, jpl::xScrollOffset, jpl::yScrollOffset;

void jpl::cursor_pos_callback(GLFWwindow* window, double xoffset, double yoffset){
    jpl::xMouseOffset = xoffset;
    jpl::yMouseOffset = yoffset;
}

void jpl::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    jpl::xScrollOffset = xoffset;
    jpl::yScrollOffset = yoffset;
}

int jpl::mouse_button, jpl::mouse_action, jpl::mouse_mods;

void jpl::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    jpl::mouse_button = button;
    jpl::mouse_action = action;
    jpl::mouse_mods = mods;
}