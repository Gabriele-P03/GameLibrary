#include "KeyInput.h"


int jpl::key_buffer, jpl::scancode_buffer, jpl::action_buffer, jpl::mods_buffer;

void jpl::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    jpl::key_buffer = key;
    jpl::scancode_buffer = scancode;
    jpl::action_buffer = action;
    jpl::mods_buffer = mods;
}

unsigned int jpl::codepoint;

void jpl::character_callback(GLFWwindow* window, unsigned int codepoint)
{
    jpl::codepoint = codepoint;
}
