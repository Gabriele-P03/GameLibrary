#include "Quaternion.h"

jgl::Quaternion::Quaternion(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
jgl::Quaternion::Quaternion(Quaternion* q) : Quaternion(q->x, q->y, q->z, q->w){}
jgl::Quaternion::Quaternion() : Quaternion(0, 0, 0, 0){}

/*
jgl::Quaternion::Quaternion(jgl::Vector3d* vec3d){

    double tetha = vec3d->angleRad(nullptr);

    this->w = cos(tetha/2);

    double sinTetha = sin(tetha/2);


    this->x = vec3d->getX() * sinTetha;
    this->y = vec3d->getY() * sinTetha;
    this->z = vec3d->getZ() * sinTetha;
}*/

jgl::Quaternion* jgl::Quaternion::add(double x, double y, double z, double w){
    this->x += x;
    this->y += y;
    this->z += z;
    this->w += w;

    return this;
}
jgl::Quaternion* jgl::Quaternion::add(Quaternion* quaternion){
    return this->add(quaternion->x, quaternion->y, quaternion->z, quaternion->w);
}

jgl::Quaternion* jgl::Quaternion::set(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;

    return this;
}
jgl::Quaternion* jgl::Quaternion::set(Quaternion* quaternion){
    return this->set(quaternion->x, quaternion->y, quaternion->z, quaternion->w);
}

jgl::Quaternion* jgl::Quaternion::mul(double x, double y, double z, double w){

    double newW = -(this->x*x + this->y*y + this->z*z);
    double newX = this->y*z - this->z*y;
    double newY = this->z*x - this->x*z;
    double newZ = this->x*y - this->y*x;

    return this->set(newX, newY, newZ, newW);
}
jgl::Quaternion* jgl::Quaternion::mul(Quaternion* quaternion){
    return this->mul(quaternion->x, quaternion->y, quaternion->z, quaternion->w);
}

jgl::Quaternion* jgl::Quaternion::cpy(){
    return new Quaternion(this);
}

double jgl::Quaternion::dot(Quaternion* q){
    return this->x*q->x + this->y*q->y + this->z*q->z + this->w*q->w;
}

jgl::Quaternion* jgl::Quaternion::conjugate(){
    this->x *= -1;
    this->y *= -1;
    this->z *= -1;

    return this;
}

double jgl::Quaternion::nor(){
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

double jgl::Quaternion::getAngle(){
    return 2 * acos(this->w);
}