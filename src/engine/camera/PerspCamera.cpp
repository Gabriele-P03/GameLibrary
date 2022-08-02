#include "PerspCamera.hpp"

jpl::PerspCamera::PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far, float viewportW, float viewportH) 
    : jpl::BaseCamera::BaseCamera(pos, target, near, far, viewportW, viewportH) {
        
    this->constraintPitch = true;
    this->FOV = FOV;

    double x, y;
    jpl::getMousePosition(&x, &y);
    this->lastX = x;
    this->lastY = y;

    this->updateFrustum();
    this->update(0);
}
jpl::PerspCamera::PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far) : jpl::PerspCamera::PerspCamera(pos, target, FOV, near, far, 0.0f, 0.0f){}
jpl::PerspCamera::PerspCamera(glm::vec3 pos, glm::vec3 target) : jpl::PerspCamera::PerspCamera(pos, target, FOV, 0.1f, 100.0f){}


void jpl::PerspCamera::setFOV(float FOV){this->FOV = FOV;}
float jpl::PerspCamera::getFOV(){return this->FOV;}