#include "Quaternion.h"

jgl::Quaternion::Quaternion(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
jgl::Quaternion::Quaternion(Quaternion* q) : Quaternion(q->x, q->y, q->z, q->w){}
jgl::Quaternion::Quaternion() : Quaternion(0, 0, 0, 0){}
jgl::Quaternion::Quaternion(jgl::Vector3f* axis, float _rad) : jgl::Quaternion(
        axis->getX() * sin(_rad/2), 
        axis->getY() * sin(_rad/2),
        axis->getZ() * sin(_rad/2),
        cos(_rad/2)
    ){
}
jgl::Quaternion::Quaternion(float yaw, float pitch, float roll){
    float cy = cos(yaw/2);
    float sy = sin(yaw/2);
    float cp = cos(pitch/2);
    float sp = sin(pitch/2);
    float cr = cos(roll/2);
    float sr = sin(roll/2);

    this->set(
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cp * cy + sr * sp * sy);
}
jgl::Quaternion::Quaternion(jgl::Matrix4* Matrix4) : jgl::Quaternion(Matrix4->getQuaternion()){}
jgl::Quaternion::Quaternion(jgl::Vector3f* vec3d) : jgl::Quaternion(vec3d->getRotationMatrix()){}
jgl::Quaternion::Quaternion(std::string* fromString){
    float firstIndex = fromString->find_first_of(',');
    float secondIndex = fromString->substr(firstIndex+1).find_first_of(',');
    float lastIndex = fromString->substr(secondIndex+1).find_first_of(',');
    
    this->x = atoi(fromString->substr(0, firstIndex).c_str());
    this->y = atoi(fromString->substr(firstIndex+1, secondIndex).c_str());
    this->z = atoi(fromString->substr(secondIndex+1, lastIndex).c_str());
    this->w = atoi(fromString->substr(lastIndex+1, fromString->length()).c_str());
}


jgl::Quaternion* jgl::Quaternion::add(float x, float y, float z, float w){
    this->x += x;
    this->y += y;
    this->z += z;
    this->w += w;

    return this;
}
jgl::Quaternion* jgl::Quaternion::add(Quaternion* quaternion){
    return this->add(quaternion->x, quaternion->y, quaternion->z, quaternion->w);
}

jgl::Quaternion* jgl::Quaternion::set(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;

    return this;
}
jgl::Quaternion* jgl::Quaternion::set(Quaternion* quaternion){
    return this->set(quaternion->x, quaternion->y, quaternion->z, quaternion->w);
}

jgl::Quaternion* jgl::Quaternion::mul(float x, float y, float z, float w){

    float newW = -(this->x*x + this->y*y + this->z*z);
    float newX = this->y*z - this->z*y;
    float newY = this->z*x - this->x*z;
    float newZ = this->x*y - this->y*x;

    return this->set(newX, newY, newZ, newW);
}
jgl::Quaternion* jgl::Quaternion::mul(Quaternion* quaternion){
    return this->mul(quaternion->x, quaternion->y, quaternion->z, quaternion->w);
}

jgl::Quaternion* jgl::Quaternion::cpy(){
    return new Quaternion(this);
}

float jgl::Quaternion::dot(Quaternion* q){
    return this->x*q->x + this->y*q->y + this->z*q->z + this->w*q->w;
}

jgl::Quaternion* jgl::Quaternion::conjugate(){
    this->x *= -1;
    this->y *= -1;
    this->z *= -1;

    return this;
}

float jgl::Quaternion::nor(){
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

float jgl::Quaternion::getAngle(){
    return 2 * acos(this->w);
}

float jgl::Quaternion::getYaw(){
    
    float test = x*y + z*w;
    if(test > 0.499){
        return M_PI_2;
    }else if(test < -0.449){
        return -M_PI_2;
    }else{
        return asin(2*test);
    }
}
float jgl::Quaternion::getRoll(){
        float test = x*y + z*w;
    if(test > 0.499){
        return 0;
    }else if(test < -0.449){
        return 0;
    }else{
        return atan2(2.0*(x*w-y*z), 1-2*pow(x,2)-2*pow(z,2));
    }
    
}
float jgl::Quaternion::getPitch(){
    float test = x*y + z*w;
    if(test > 0.499){
        return 2*atan2(x, w);
    }else if(test < -0.449){
        return -2*atan2(x, w);
    }else{
        return atan2(2*(y*w-x*z) , 1 - 2*pow(y,2) - 2*pow(z,2));
    }
}



jgl::Vector3f* jgl::Quaternion::getDirectionVector(){
    return (new jgl::Matrix4(this))->getRotation();
}



float jgl::Quaternion::getX(){return this->x;}
float jgl::Quaternion::getY(){return this->y;}
float jgl::Quaternion::getZ(){return this->z;}
float jgl::Quaternion::getW(){return this->w;}