#include "OrthoCamera.hpp"

jpl::OrthoCamera::OrthoCamera(glm::vec3 pos, glm::vec3 target, float near, float far, float viewportW, float viewportH) 
    : jpl::BaseCamera::BaseCamera(pos, target, near, far, viewportW, viewportH) {
        
    this->updateFrustum();
    this->update(0);
}
jpl::OrthoCamera::OrthoCamera(glm::vec3 pos, glm::vec3 target, float near, float far) : jpl::OrthoCamera::OrthoCamera(pos, target, near, far, 0.0f, 0.0f){}
jpl::OrthoCamera::OrthoCamera(glm::vec3 pos, glm::vec3 target) : jpl::OrthoCamera::OrthoCamera(pos, target, 0.1f, 100.0f){}


void jpl::OrthoCamera::updateFrustum(){
    float vW_2 = this->viewportW/2.0f, vH_2 = this->viewportH / 2.0f;
    this->projection = glm::ortho(0.0f, vW_2, 0.0f, vH_2, this->near, this->far);
}

void jpl::OrthoCamera::tick(float speedMov, float speedRot, unsigned int shaderProgram){

    float x = 0.0f, y = 0.0f, z = 0.0f;

    if(jpl::isKeyPressed(GLFW_KEY_W)){
        y = speedMov;
    }
    if(jpl::isKeyPressed(GLFW_KEY_S)){
        y = -speedMov;
    }
    if(jpl::isKeyPressed(GLFW_KEY_A)){
        x = speedMov;
    }
    if(jpl::isKeyPressed(GLFW_KEY_D)){
        x = -speedMov;
    }
    if(jpl::isKeyPressed(GLFW_KEY_Y)){
        z = speedMov;
    }
    if(jpl::isKeyPressed(GLFW_KEY_H)){
        z = -speedMov;
    }

    if(x != 0.0f || y != 0.0f || z != 0.0f){
        this->position += glm::vec3(x, y, z);
        this->update(shaderProgram);
    }
}