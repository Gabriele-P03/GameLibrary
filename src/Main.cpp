#include "Main.h"

using namespace jpl;

int main(int argc, const char* argv[]){  

    initializeGameLibrary();
    int hints[] = {GLFW_RESIZABLE, GLFW_VISIBLE};
    int values[] = {GLFW_TRUE, GLFW_FALSE};
    createWindow(-1, -1, "Ciao", NULL, NULL, &hints[0], &values[0], 2, true);

    jpl::PerspCamera* camera = new jpl::PerspCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), M_PI_2, 0.1f, 100.0f, jpl::WindowSize::INSTANCE.w/60, jpl::WindowSize::INSTANCE.h/60);
    jpl::ModelShader* modelShader = new jpl::ModelShader();
    jpl::Mesh* mesh = jpl::loadModel("model/block.obj", 3);
    camera->pushCombinedMatrix(*modelShader->getShaderProgram());
    jpl::Texture* texture = new jpl::Texture("model/texture.png");

    std::cout<<"Beginning render loop...\n\n";
    while(!glfwWindowShouldClose(window)){
        
        if(isKeyPressed(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        
        camera->tick(0.05f, 0.05f, *modelShader->getShaderProgram());
        texture->draw();
        modelShader->render(jpl::Mesh::CUBE, 0.0f, 0.0f, 0.0f);
        //modelShader->rotation = glm::rotate(modelShader->rotation, (float)M_PI_2/90, glm::vec3(1.0f, 0.0f, 0.0f));
        //modelShader->render(mesh, 2.0f, 2.0f, 2.0f);

        if(jpl::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
            std::cout<<"pos: "<<camera->position.x<<" - "<<camera->position.y<<" - "<<camera->position.z<<"\n";
            std::cout<<"dir: "<<camera->direction.x<<" - "<<camera->direction.y<<" - "<<camera->direction.z<<"\n\n";
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminateGameLibrary();
    
    return 0;
}

void initializeGameLibrary(){

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

void createWindow(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share, int* hints, int* values, u_int _lenght, bool show){
    
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

void terminateGameLibrary(){

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

void error_callback(int error, const char* desc){
    fprintf(stderr, "Error: %d: %s\n", error, desc);
}