#include "Main.h"

using namespace jpl;

int main(int argc, const char* argv[]){  

    jpl::View* view = new jpl::View(0, 0, 100, 100);
    view->setOnClickListener(
        [](jpl::View* v){
            v->getH();
        }
    );
    /*
    initializeGameLibrary();
    int hints[] = {GLFW_RESIZABLE, GLFW_VISIBLE};
    int values[] = {GLFW_TRUE, GLFW_FALSE};
    createWindow(-1, -1, "Ciao", NULL, NULL, &hints[0], &values[0], 2, true);

    jpl::Audio* audio = new jpl::Audio(new jpl::AudioFile("a.wav"));
    jpl::PerspCamera* camera = new jpl::PerspCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), M_PI_2, 0.1f, 100.0f, jpl::WindowSize::INSTANCE.w/60, jpl::WindowSize::INSTANCE.h/60);
    jpl::ModelShader* modelShader = new jpl::ModelShader();
    jpl::Mesh* mesh = jpl::loadModel("model/block.obj", 3);
    camera->pushCombinedMatrix(*modelShader->getShaderProgram());
    jpl::Texture* texture = new jpl::Texture("model/texture.png");

    std::cout<<"Beginning render loop...\n\n";
    
    audio->play();

    while(!glfwWindowShouldClose(window)){
        
        if(isKeyPressed(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        
        texture->draw();
        modelShader->render(mesh, 2.0f, 2.0f, 2.0f);
        camera->tick(0.05f, 0.05f, *modelShader->getShaderProgram());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminateGameLibrary();
    */
    return 0;
}
