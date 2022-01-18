#include "BaseCamera.hpp"


jpl::BaseCamera::BaseCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far){

    this->position = position;
    this->direction = direction;
    this->up = (this->direction->crs(&jgl::Vector3f::yAxis))->crs(this->direction);
    this->near = near;
    this->far = far;

}


void jpl::BaseCamera::lookAt(float x, float y, float z){
    //this->lookAt(new jgl::Vector3f(x, y, z));
    //This code will be written in PerspectiveCamera
}
void jpl::BaseCamera::lookAt(jgl::Vector3f* target){
    /*
    this->direction->set(
        target->cpy()->addAll(
            -this->position->getX(),
            -this->position->getY(),
            -this->position->getZ()
        )->vrs());
    
        This code will be written in PerspectiveCamera
    */
}



void jpl::BaseCamera::normalizeUp(){
    this->up->set(this->direction->crs(this->up)->crs(direction));
}


jgl::Vector3f* jpl::BaseCamera::project(jgl::Vector3f* worldCoords){
    return nullptr;
}

jgl::Vector3f* jpl::BaseCamera::unproject(jgl::Vector3f* worldCoords){
    return nullptr;
}


void jpl::BaseCamera::setToRotation(jgl::Quaternion* quaternion){
    this->direction = quaternion->getDirectionVector();
}
void jpl::BaseCamera::rotate(jgl::Quaternion* quaternion){
    this->rotate(new jgl::Matrix4(quaternion));
}
void jpl::BaseCamera::rotate(jgl::Matrix4* rotationMatrix){
    this->direction->set(  ((new jgl::Matrix4(this->direction))->mul(rotationMatrix))->getRotation());
}
void jpl::BaseCamera::rotateAround(jgl::Vector3f* point, jgl::Matrix4* rotationMatrix){

    jgl::Vector3f* difPos = this->position->cpy()->addAll(-point->getX(), -point->getY(), -point->getZ());

    jgl::Matrix4* transform = new jgl::Matrix4();
    transform->setToTranslation(difPos, true);
    transform->mul(rotationMatrix);
    transform->translate(point);

    this->position = transform->getTranslation();
}

void jpl::BaseCamera::transform(jgl::Matrix4* transformMatrix){

    jgl::Matrix4* currentMatrix = new jgl::Matrix4(this->direction);
    currentMatrix->translate(this->position);
    currentMatrix->mul(transformMatrix);

    this->direction = currentMatrix->getRotation()->crs(&jgl::Vector3f::yAxis);
    this->position = currentMatrix->getTranslation();
    this->normalizeUp();
}

void jpl::BaseCamera::translate(jgl::Vector3f* translatingVector){
    this->position->add(translatingVector);
}
void jpl::BaseCamera::setToTranslation(jgl::Vector3f* translatingVector){
    this->position = translatingVector;
}

void jpl::BaseCamera::update(){
    this->view = (new jgl::Matrix4(this->direction))->setToTranslation(this->position, true);
/*
    this->projection = new jgl::Matrix4(    
                    1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, -1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
    );
    //For cenetering camera about window's origin(0;0)
    this->projection->setToScale(2.0f/(float)this->viewportW, 2.0f/(float)this->viewportH, 2.0f/(float)(far-near), true);
    this->projection->translate(new jgl::Vector3f(this->viewportW/2, this->viewportH/2, (-this->near -this->far)/2));

    this->combined = this->view->cpy()->mul(this->projection);
*/
}

void jpl::BaseCamera::setFrustum(float near, float far){
    this->near = near;
    this->far = far;
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