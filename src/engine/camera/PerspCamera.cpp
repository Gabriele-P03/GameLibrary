#include "PerspCamera.hpp"

jpl::PerspCamera::PerspCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far) :
    jpl::BaseCamera(position, direction, near, far){

    
    this->update();
}

void jpl::PerspCamera::translate(float x, float y, float z){
    this->translate(new jgl::Vector3f(x, y, z));
}
void jpl::PerspCamera::translate(jgl::Vector3f* translatingVector){
    this->position->add(translatingVector);
}

void jpl::PerspCamera::rotate(float yaw, float pitch, float roll){
    this->rotate(new jgl::Matrix4(yaw, pitch, roll));
}
void jpl::PerspCamera::rotate(jgl::Quaternion* q){
    this->rotate(new jgl::Matrix4(q));
}
void jpl::PerspCamera::rotate(jgl::Matrix4* mat){
    jpl::BaseCamera::rotate(mat);
}

void jpl::PerspCamera::setFOV(float FOV){
    this->FOV = FOV;
}