#include "Main.hpp"

using namespace jpl;

int main(int argc, const char* argv[]){  

    initializeGameLibrary();
    int hints[] = {GLFW_RESIZABLE, GLFW_VISIBLE};
    int values[] = {GLFW_TRUE, GLFW_FALSE};
    createWindow(-1, -1, "Ciao", NULL, NULL, &hints[0], &values[0], 2, true);

    jpl::TestScene* test = new jpl::TestScene();
    jpl::SceneManager* sceneManager = new jpl::SceneManager();
    sceneManager->addScene(test);
    sceneManager->setIDScene(test->getID());


    std::cout<<"Beginning render loop...\n\n";

    while(!glfwWindowShouldClose(window)){
        
        if(isKeyPressed(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT); 
        
        sceneManager->tick();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminateGameLibrary();
    
    return 0;
}
