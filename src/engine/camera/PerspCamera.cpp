#include "PerspCamera.hpp"

jpl::PerspCamera::PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far, float viewportW, float viewportH) 
    : jpl::BaseCamera::BaseCamera(pos, target, near, far, viewportW, viewportH) {
        
    this->FOV = FOV;
    this->updateFrustum();
    this->update(0);
}
jpl::PerspCamera::PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far) : jpl::PerspCamera::PerspCamera(pos, target, FOV, near, far, 0.0f, 0.0f){}
jpl::PerspCamera::PerspCamera(glm::vec3 pos, glm::vec3 target) : jpl::PerspCamera::PerspCamera(pos, target, FOV, 0.1f, 100.0f){}


void jpl::PerspCamera::updateFrustum(){
    float vW_2 = this->viewportW/2.0f, vH_2 = this->viewportH / 2.0f;
    this->projection = glm::perspective(
        this->FOV, this->viewportW/this->viewportH, this->near, this->far
    );
}

void jpl::PerspCamera::updateView(){
    this->view = glm::lookAt(this->position, this->position + this->direction, this->up);
}

void jpl::PerspCamera::tick(float speedMov, float speedRot, unsigned int shaderProgram){

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

void jpl::PerspCamera::setFOV(float FOV){this->FOV = FOV;}
float jpl::PerspCamera::getFOV(){return this->FOV;}