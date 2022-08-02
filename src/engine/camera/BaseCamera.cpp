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



void jpl::BaseCamera::setViewport(float viewportW, float viewportH){
    this->viewportW = viewportW;
    this->viewportH = viewportH;
}


void jpl::BaseCamera::pushCombinedMatrix(unsigned int shaderProgram){
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "combined"), 1, GL_FALSE, glm::value_ptr(this->combined));
}