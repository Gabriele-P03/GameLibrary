#include "OrthoCamera.hpp"

jpl::OrthoCamera::OrthoCamera(jgl::Vector3f* position, float near, float far, float viewportW, float viewportH) : 
    jpl::BaseCamera::BaseCamera(position, new jgl::Vector3f(0.0f, 0.0f, 1.0f), near, far){
}
jpl::OrthoCamera::OrthoCamera(jgl::Vector3f* position, float viewportW, float viewportH) :
    jpl::OrthoCamera::OrthoCamera(position, 0.0f, 10.0f, viewportW, viewportH){
}
jpl::OrthoCamera::OrthoCamera() : 
    jpl::OrthoCamera::OrthoCamera(1.0f, -10.0f){

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
    this->direction->rotate(angle, &jgl::Vector3f::zAxis);
}
void jpl::OrthoCamera::rotateAround(jgl::Vector2f* point, float angle){
    this->position->rotateAround(new jgl::Vector3f(point->getX(), point->getY(), 0.0f), angle, &jgl::Vector3f::xAxis);
}


void jpl::OrthoCamera::translate(jgl::Vector3f* translatingVector){
    this->position->addAll(translatingVector->getX(), translatingVector->getY(), 0.0f);
}
void jpl::OrthoCamera::translate(float x, float y, float z){
    this->position->addAll(x, y, z);
}
void jpl::OrthoCamera::setToTranslation(jgl::Vector3f* translationVector){
    this->position = new jgl::Vector3f(translationVector->getX(), translationVector->getY(), translationVector->getZ());
}
void jpl::OrthoCamera::setToTranslation(float x, float y, float z){
    this->position = new jgl::Vector3f(x, y, z);
}


void jpl::OrthoCamera::updateFrustum(){
    this->projection = (new jgl::Matrix4())->setToScale(
            (float)jpl::WindowSize::INSTANCE.w/this->viewportW, 
            (float)jpl::WindowSize::INSTANCE.h/this->viewportH,
            1.0f, 
            true);
}


void jpl::OrthoCamera::setToOrtho(float newViewportW, float newViewportH){
    jpl::BaseCamera::viewportW = newViewportW;
    jpl::BaseCamera::viewportH = newViewportH;
}

jgl::Vector2f* jpl::OrthoCamera::project(jgl::Vector2f* mouseCoords){

    //y is calculated from +1 'cause y mouse coord begins from top side of the window
    float x = mouseCoords->getX()/jpl::WindowSize::INSTANCE.w;
    float y = (jpl::WindowSize::INSTANCE.h - mouseCoords->getY())/jpl::WindowSize::INSTANCE.h;
    x *= this->viewportW;
    y *= this->viewportH;

    return new jgl::Vector2f(
        x + this->position->getX(),
        y + this->position->getY()
    );
}

jgl::Vector2f* jpl::OrthoCamera::unproject(jgl::Vector2f* worldCoords){

    float x = worldCoords->getX() - this->position->getX();
    float y = worldCoords->getY() - this->position->getY();

    x /= this->viewportW;
    y /= this->viewportH;

    x *= jpl::WindowSize::INSTANCE.w;
    y *= jpl::WindowSize::INSTANCE.h;
    y += jpl::WindowSize::INSTANCE.h;

    return new jgl::Vector2f(x, y);
}