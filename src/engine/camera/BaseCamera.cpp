#include "BaseCamera.hpp"


jpl::BaseCamera::BaseCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far){

    this->position = position;
    this->direction = direction;
    this->up = new jgl::Vector3f(0.0f, 1.0f, 0.0f);
    this->normalizeUpAndRight();
    this->near = near;
    this->far = far;

    this->view = new jgl::Matrix4();
    this->projection = new jgl::Matrix4();
}


void jpl::BaseCamera::tick(float speed){

    float x = 0.0f, y = 0.0f;

    if(isKeyPressed(GLFW_KEY_W)){
        y += speed;
    }
    if(isKeyPressed(GLFW_KEY_S)){
        y -= speed;
    }
    if(isKeyPressed(GLFW_KEY_A)){
        x -= speed;
    }
    if(isKeyPressed(GLFW_KEY_D)){
        x += speed;
    }

    if(x != 0.0f || y != 0.0f){
        this->position->addAll(x, y, 0.0f);
    }
}


void jpl::BaseCamera::lookAt(float x, float y, float z){
    this->lookAt(new jgl::Vector3f(x, y, z));
}
void jpl::BaseCamera::lookAt(jgl::Vector3f* target){
    this->direction->set(
        target->cpy()->addAll(
            -this->position->getX(),
            -this->position->getY(),
            -this->position->getZ()
        )->vrs());

    //Recalculate up and right vector
    this->normalizeUpAndRight();
}



void jpl::BaseCamera::normalizeUpAndRight(){
    this->right = this->direction->crs(this->up);
    this->up = this->right->crs(this->direction);
}


void jpl::BaseCamera::update(){
    this->view->set( new float[16]{
        this->right->getX(), this->right->getY(), this->right->getZ(), 0.0f,
        this->up->getX(), this->up->getY(), this->up->getZ(), 0.0f,
        this->direction->getX(), this->direction->getY(), this->direction->getZ(), 0.0f,
        this->position->getX(), this->position->getY(), this->position->getZ(), 1.0f
    });
    this->combined = this->projection->cpy()->mul(this->view);
}

void jpl::BaseCamera::updateFrustum(){

}

void jpl::BaseCamera::setPlane(float near, float far){
    this->near = near;
    this->far = far;
}

void jpl::BaseCamera::setFOV(float FOV){
    this->FOV = FOV;
}

void jpl::BaseCamera::setViewport(float viewportW, float viewportH){
    this->viewportW = viewportW;
    this->viewportH = viewportH;
}

jgl::Matrix4* jpl::BaseCamera::getViewMatrix(){return this->view;}
jgl::Matrix4* jpl::BaseCamera::getProjectionMatrix(){return this->projection;}
jgl::Matrix4* jpl::BaseCamera::getCombinedMatrix(){return this->combined;}
jgl::Vector3f* jpl::BaseCamera::getDirection(){return this->direction;}
jgl::Vector3f* jpl::BaseCamera::getPosition(){return this->position;}
jgl::Vector3f* jpl::BaseCamera::getUp(){return this->up;}
float jpl::BaseCamera::getFar(){return this->far;}
float jpl::BaseCamera::getNear(){return this->near;}
float jpl::BaseCamera::getViewportH(){return this->viewportH;}
float jpl::BaseCamera::getViewportW(){return this->viewportW;}