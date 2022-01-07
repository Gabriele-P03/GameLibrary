#include "BaseCamera.hpp"


jpl::BaseCamera::BaseCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far){

    this->position = position;
    this->direction = direction;
    this->up = (this->direction->crs(&jgl::Vector3f::yAxis))->crs(this->direction);
    this->near = near;
    this->far = far;
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
}



void jpl::BaseCamera::normalizeUp(){
    this->up->set(this->direction->crs(this->up)->crs(direction));
}


void jpl::BaseCamera::rotate(jgl::Quaternion* quaternion){
    this->rotate(new jgl::Matrix4(quaternion));
}
void jpl::BaseCamera::rotate(jgl::Matrix4* rotationMatrix){
    this->direction->set(  ((new jgl::Matrix4(this->direction))->mul(rotationMatrix))->getRotation());
}


void jpl::BaseCamera::rotateAround(jgl::Vector3f* point, jgl::Matrix4* rotationMatrix){

    jgl::Vector3f* difPos = this->position->cpy()->addAll(-point->getX(), -point->getY(), -point->getZ());

    jgl::Matrix4* transform = new jgl::Matrix4(this->direction);
    transform->translate(this->position);
    transform->mul(rotationMatrix);
    this->direction = transform->getRotation();

    this->position = transform->getTranslation();
    this->position->add(point);
}