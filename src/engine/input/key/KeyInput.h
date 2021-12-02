#ifndef KEYINPY_H
#define KEYINPUT_H

#include <GLFW/glfw3.h>

int getStateKey(int key);

bool isKeyPressed(int key);

bool isKeyReleased(int key);

int getKeyScancode(int key);

#endif