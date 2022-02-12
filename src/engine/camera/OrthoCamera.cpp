#include "OrthoCamera.hpp"

jpl::OrthoCamera::OrthoCamera(jgl::Vector3f* position, float near, float far, float viewportW, float viewportH) : 
    jpl::BaseCamera::BaseCamera(position, new jgl::Vector3f(0.0f, 0.0f, 1.0f), near, far){

        this->FOV = M_PI_2;
        this->setToOrtho(viewportW, viewportH);
        this->update();
}
jpl::OrthoCamera::OrthoCamera(jgl::Vector3f* position, float viewportW, float viewportH) :
    jpl::OrthoCamera::OrthoCamera(position, 0.0f, 10.0f, viewportW, viewportH){
}
jpl::OrthoCamera::OrthoCamera() : 
    jpl::OrthoCamera::OrthoCamera(0.0f, -10.0f){

}
jpl::OrthoCamera::OrthoCamera(float near, float far) :
    jpl::BaseCamera::BaseCamera(new jgl::Vector3f(0.0f, 0.0f, 0.0f), new jgl::Vector3f(0.0f, 0.0f, -1.0f), near, far){
        //Neither call setToOrtho nor update
}
jpl::OrthoCamera::OrthoCamera(float near, float far, float viewportW, float viewportH) : 
    jpl::OrthoCamera::OrthoCamera(new jgl::Vector3f(0.0f, 0.0f, 0.0f), near, far, viewportW, viewportH){

}

void jpl::OrthoCamera::setToRotation(float angle){
    this->direction = (new jgl::Quaternion(new jgl::Vector3f(0.0f, 0.0f, 1.0f), angle))->getDirectionVector();
}
void jpl::OrthoCamera::rotate(float angle){
    //this->direction->rotate(angle, &jgl::Vector3f::zAxis);
    jpl::BaseCamera::rotate(new jgl::Quaternion(this->getDirection(), angle));
}
void jpl::OrthoCamera::rotateAround(jgl::Vector2f* point, float angle){
    jpl::BaseCamera::rotateAround(new jgl::Vector3f(point->getX(), point->getY(), this->direction->getZ()), new jgl::Matrix4(angle, 0.0f, 0.0f));
}


void jpl::OrthoCamera::translate(jgl::Vector2f* translatingVector){
    this->position->addAll(translatingVector->getX(), translatingVector->getY(), 0.0f);
}
void jpl::OrthoCamera::translate(float x, float y){
    this->translate(new jgl::Vector2f(x, y));
}
void jpl::OrthoCamera::setToTranslation(jgl::Vector2f* translationVector){
    this->position = new jgl::Vector3f(translationVector->getX(), translationVector->getY(), this->position->getZ());
}
void jpl::OrthoCamera::setToTranslation(float x, float y){
    this->position = new jgl::Vector3f(x, y, this->position->getZ());
}


void jpl::OrthoCamera::update(){
    jpl::BaseCamera::update();

    int w, h;
    glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);

    this->projection = (new jgl::Matrix4())->setToScale((float)w/this->viewportW, (float)h/this->viewportH, 1.0f, true);
    this->combined = this->projection->cpy()->mul(this->view);
}


void jpl::OrthoCamera::setToOrtho(float newViewportW, float newViewportH){
    jpl::BaseCamera::viewportW = newViewportW;
    jpl::BaseCamera::viewportH = newViewportH;
}