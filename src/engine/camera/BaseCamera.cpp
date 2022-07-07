#include "BaseCamera.hpp"

jpl::BaseCamera::BaseCamera(glm::vec3 pos, glm::vec3 target, float near, float far, float viewportW, float viewportH){
    this->position = pos;
    this->target = target;
    this->near = near;
    this->far = far;
    this->direction = glm::normalize(pos - target);
    this->setViewport(viewportW, viewportH);
    this->updateUpAndRight();
}
jpl::BaseCamera::BaseCamera(glm::vec3 pos, glm::vec3 target, float near, float far) : jpl::BaseCamera::BaseCamera(pos, target, near, far, 0.0f, 0.0f){}
jpl::BaseCamera::BaseCamera(glm::vec3 pos, glm::vec3 target) : jpl::BaseCamera::BaseCamera(pos, target, 0.1f, 100.0f){}

void jpl::BaseCamera::updateUpAndRight(){

    this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->direction));
    this->up = glm::normalize(glm::cross(this->direction, this->right));
}

void jpl::BaseCamera::updateView(){
    this->view = glm::mat4(
        this->right.x, this->right.y, this->right.z, 0.0f,
        this->up.x, this->up.y, this->up.z, 0.0f,
        this->direction.x, this->direction.y, this->direction.z, 0.0f,
        this->position.x, this->position.y, this->position.z, 1.0f
    );
}

void jpl::BaseCamera::updateFrustum(){
    
}

void jpl::BaseCamera::update(unsigned int shaderProgram){
    this->updateView();
    this->combined =  this->projection * this->view;
    std::cout<<"pos: "<<this->combined[3][0]<<" - "<<this->combined[3][1]<<" - "<<this->combined[3][2]<<std::endl;
    if(shaderProgram > 0)
        this->pushCombinedMatrix(shaderProgram);
}

void jpl::BaseCamera::tick(float speedMov, float speedRot, unsigned int shaderProgram){
    
}

void jpl::BaseCamera::setViewport(float viewportW, float viewportH){
    this->viewportW = viewportW;
    this->viewportH = viewportH;
}


void jpl::BaseCamera::pushCombinedMatrix(unsigned int shaderProgram){
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "combined"), 1, GL_FALSE, glm::value_ptr(this->combined));
}