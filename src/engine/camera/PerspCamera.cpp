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

    bool update = false;

    if(jpl::isKeyPressed(GLFW_KEY_W)){
        this->move(direction, speedMov);
        update = true;
    }
    if(jpl::isKeyPressed(GLFW_KEY_S)){
        this->move(direction, -speedMov);
        update = true;
    }
    if(jpl::isKeyPressed(GLFW_KEY_A)){
        this->move(glm::cross(this->up, this->direction), speedMov);
        update = true;
    }
    if(jpl::isKeyPressed(GLFW_KEY_D)){
        this->move(glm::cross(this->direction, this->up), speedMov);
        update = true;
    }

    //Let's check if mouse has been moved
    double currentX, currentY;
    jpl::getMousePosition(&currentX, &currentY);
    if(this->lastX != currentX || this->lastY != currentY){

        float yaw = currentX - lastX;
        float pitch = lastY - currentY;//Since screen is bottom to top

        this->YAW += yaw;

        if(!this->constraintPitch || 
            (this->constraintPitch && this->PITCH+pitch <= 89.0f && this->PITCH+pitch >= -89.0f))
            this->PITCH += pitch;


        this->lastX = currentX;
        this->lastY = currentY;

        this->direction.x = cos(glm::radians(this->YAW)) * cos(glm::radians(this->PITCH));
        this->direction.y = sin(glm::radians(this->PITCH));
        this->direction.z = sin(glm::radians(this->YAW)) * cos(glm::radians(this->PITCH));

        this->direction = glm::normalize(this->direction);

        this->updateUpAndRight();
        update = true;
    }

    if(update)
        this->update(shaderProgram);
}

inline void jpl::PerspCamera::move(glm::vec3 direction, float speed){
    glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));

    //In order to move ignoring y-axis
    right.y = 0.0f;
    right = glm::normalize(right);

    direction = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), right));
    this->position += direction * speed;
}

void jpl::PerspCamera::setFOV(float FOV){this->FOV = FOV;}
float jpl::PerspCamera::getFOV(){return this->FOV;}