#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "engine/input/key/KeyInput.h"
#include "engine/graphics/shader/Shader.h"
#include "files/Files.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/graphics/shader/cubeShader/CubeShader.hpp"
#include "engine/math/vector/v2/Vector2d.h"
#include "engine/math/matrix/mat4/Matrix4d.h"
#include "engine/math/matrix/mat3/Matrix3d.h"
#include "engine/parser/json/JsonReader.h"
#include "engine/parser/json/JsonWriter.h"
#include "engine/audio/Audio.h"

//This will be the main window of the game
GLFWwindow* window;

using namespace std;

/**
 * First method to have to be called:
 * 
 * Set the error callback;
 * Initialize library calling glfwInit();
 */ 
void initializeGameLibrary();

/**
 * Error callback.
 * Just print error code @param error and @param desc
 */ 
void error_callback(int error, const char* desc);

/**
 * Create window with the given parameters.
 * See glfwCreateWindow() for more details about parameters.
 * 
 * Window hints must be set before its creation. You can pass an array of hints and one of values.
 * Be aware of their lenght...
 * 1) Full-Screen: monitor != NULL
 * 2) Sized: w > 0 and h > 0 and monitor = NULL
 * 3) Max-Sized: w = -1 and h = -1 and monitor = NULL
 * 
 * On Window, we have to use GLEW in order to call OpenGl's functions, then 
 * we must before call glewInit()
 * 
 * @param w width of the window
 * @param h height of the window
 * @param title title of the window
 * @param monitor 
 * @param share
 * @param hints array of hints of the window
 * @param values array of values of the window's hints
 * @param _lenght len of hints and values parameters
 * @param show if window must be showed just it has been created
 */ 
void createWindow(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share, 
                         int* hints, int* values, u_int _lenght, bool show);

/**
 * Terminate OpenAl, GLFW and, if on window, terminate GLEW
 * Set the error callback to NULL in order to free it
 * Destroy given window.
 * Terminate library.
 * 
 * Called on game closing
 */ 
void terminateGameLibrary();

#endif