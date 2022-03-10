#include "PerspCamera.hpp"

jpl::PerspCamera::PerspCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far) :
    jpl::BaseCamera(position, direction, near, far){
}

void jpl::PerspCamera::translate(jgl::Vector3f* translatingVector){
    this->position->add(translatingVector);
}
void jpl::PerspCamera::setToTranslation(jgl::Vector3f* translatingVector){
    this->position = translatingVector;
}

void jpl::PerspCamera::setToRotation(jgl::Quaternion* quaternion){
    this->direction = quaternion->getDirectionVector();
}
void jpl::PerspCamera::rotate(jgl::Quaternion* quaternion){
    this->rotate(new jgl::Matrix4(quaternion));
}
void jpl::PerspCamera::rotate(jgl::Matrix4* rotationMatrix){
    this->direction->set(  ((new jgl::Matrix4(this->direction))->mul(rotationMatrix))->getRotation());
}
void jpl::PerspCamera::rotateAround(jgl::Vector3f* point, jgl::Matrix4* rotationMatrix){

    jgl::Vector3f* difPos = this->position->cpy()->addAll(-point->getX(), -point->getY(), -point->getZ());

    jgl::Matrix4* transform = new jgl::Matrix4();
    transform->setToTranslation(difPos, true);
    transform->mul(rotationMatrix);
    transform->translate(point);

    this->position = transform->getTranslation();
}

void jpl::PerspCamera::transform(jgl::Matrix4* transformMatrix){

    jgl::Matrix4* currentMatrix = new jgl::Matrix4(this->direction);
    currentMatrix->translate(this->position);
    currentMatrix->mul(transformMatrix);

    this->direction = currentMatrix->getRotation()->crs(&jgl::Vector3f::yAxis);
    this->position = currentMatrix->getTranslation();
    this->normalizeUpAndRight();
}
