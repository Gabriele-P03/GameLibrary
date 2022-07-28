#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>


#define _USE_MATH_DEFINES
#include <cmath>

#include "engine/camera/PerspCamera.hpp"
#include "engine/graphics/shader/ModelShader.hpp"
#include "engine/graphics/model/ModelLoader.hpp"
#include "engine/graphics/texture/Texture.hpp"
#include "engine/graphics/shader/TextureShader.hpp"
#include "engine/graphics/shader/TextShader.hpp"
#include "engine/input/key/KeyInput.h"
#include "engine/utils/WindowInfo.hpp"
#include "engine/audio/Audio.h"
#include "engine/view/View.hpp"

#define PM_JPL
#define _USE_PHYSICS_DEFINES_JPL
#include "engine/physics/Kinematics.hpp"

//This will be the main window of the game
GLFWwindow* window;

using namespace std;

/**
 * Error callback.
 * Print error code @param error and @param desc
 */ 
void error_callback(int error, const char* desc){
    fprintf(stderr, "Error: %d: %s\n", error, desc);
}


/**
 * First method to have to be called:
 * 
 * Set the error callback;
 * Initialize library calling glfwInit();
 */ 
inline void initializeGameLibrary(){

    #ifdef __linux__
        std::cout<<"OS detected: Linux\n\n\n";
    #elif _WIN32
        std::cout<<"OS Detected: Window\n\n";
    #endif

    std::cout<<"Initializing Game Library...\n\n";

    std::cout<<"Setting Error Callback...";
    glfwSetErrorCallback(error_callback);
    std::cout<<"Done\n";

    std::cout<<"Initializing GLFW...";
    if(!glfwInit()){
        std::cout<<"Could not initialize GLFW...\n";
        exit(-1);
    }

    std::cout<<"Done\n";

    #ifdef AUDIO_JPL_H
        initAudio();
    #endif

    std::cout<<"Everything initialized!\n\n";
}


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
inline void createWindow(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share, 
                         int* hints, int* values, u_int _lenght, bool show){


    std::cout<<"\nCreating window...\n\nHints: ";

    //Setting hints
    if(hints != NULL && values != NULL){
        for(int i = 0; i < _lenght; i++){
            glfwWindowHint(hints[i], values[i]);
            std::cout<<"( "<<hints[i]<<" - "<<values[i]<<" )   ";
        }
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //If monitor is NULL, according to documentation, a full screen window will be created
    if(monitor != NULL){
        w = 1; h = 1;
    }else{
        //If width and height are equal to -1, a max sized window will be created
        if(w == -1 && h == -1){
            glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), new int, new int, &w, &h);
        }
    }

    std::cout<<"\nWindow's values at creation: Width="<<w<<" Height="<<h<<"\n";
    window = glfwCreateWindow(w, h, title, monitor, share);
            
    glfwSetWindowSizeCallback(window, jpl::window_size_callback);
    std::cout<<"Window Size Callback set\n";
    glfwSetFramebufferSizeCallback(window, jpl::framebuffer_size_callback);
    std::cout<<"Framebuffer Size Callback set\n";
    
    std::cout<<"Creation window...Done\nMaking context current...";
    glfwMakeContextCurrent(window);
    std::cout<<"Done!\n";

    /*
        In order to use OpenGl functions, we must before initialize GLEW.
    
        WARNING: glewInit() must be called always after have made context current via
        glfwMakeContextCurrent(GLFWwindow* window)
    */
        std::cout<<"Initializing GLEW...";
        int err;
        glewExperimental=true;
        if( (err = glewInit()) != GLEW_OK){
            std::cout<<"Error during GLEW initializing: "<<glewGetErrorString(err);
            exit(-1);
        }

    std::cout<<"Done\n\n";

    jpl::WindowSize::INSTANCE.w = w;
    jpl::WindowSize::INSTANCE.h = h;

    std::cout<<"Setting Keyboard Callback...";
    glfwSetKeyCallback(glfwGetCurrentContext(), jpl::keyboard_callback);
    std::cout<<"Done\nSetting Cursor Pos Callback...";
    glfwSetCursorPosCallback(glfwGetCurrentContext(), jpl::cursor_pos_callback);
    std::cout<<"Done\nSetting Scroll Callback...";
    glfwSetScrollCallback(glfwGetCurrentContext(), jpl::scroll_callback);
    std::cout<<"Done\n\n";

    if(show){
        std::cout<<"Showing window...";
        glfwShowWindow(window);
        std::cout<<"Done\n";
    }else{
        std::cout<<"You told me to not show window. Remember to do it\n\n";
    }
}

/**
 * Terminate OpenAl, GLFW and, if on window, terminate GLEW
 * Set the error callback to NULL in order to free it
 * Destroy given window.
 * Terminate library.
 * 
 * Called on game closing
 */ 
inline void terminateGameLibrary(){
    
    std::cout<<"Terminating library...\n\n";

    #ifdef AUDIO_JPL_H
        termAudio();
    #endif

    #ifdef SHADER_JPL_H
        termShaders();
    #endif

    std::cout<<"Closing GLFW...";
    glfwTerminate();
    std::cout<<"Done\n\nEverything closed!\n";
}

/**
 * 
 */ 

#endif