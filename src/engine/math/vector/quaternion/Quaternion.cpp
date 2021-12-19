#include "Quaternion.h"

jgl::Quaternion::Quaternion(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
jgl::Quaternion::Quaternion(Quaternion* q) : Quaternion(q->x, q->y, q->z, q->w){}
jgl::Quaternion::Quaternion() : Quaternion(0, 0, 0, 0){}
jgl::Quaternion::Quaternion(jgl::Vector3d* axis, double _rad) : jgl::Quaternion(
        axis->getX() * sin(_rad/2), 
        axis->getY() * sin(_rad/2),
        axis->getZ() * sin(_rad/2),
        cos(_rad/2)
    ){
}
jgl::Quaternion::Quaternion(double yaw, double pitch, double roll){
    double cy = cos(yaw/2);
    double sy = sin(yaw/2);
    double cp = cos(pitch/2);
    double sp = sin(pitch/2);
    double cr = cos(roll/2);
    double sr = sin(roll/2);

    this->set(
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cp * cy + sr * sp * sy);
}
jgl::Quaternion::Quaternion(jgl::Matrix4d* matrix4d) : jgl::Quaternion(matrix4d->getQuaternion()){}
jgl::Quaternion::Quaternion(jgl::Vector3d* vec3d) : jgl::Quaternion(vec3d->getRotationMatrix()){}
jgl::Quaternion::Quaternion(std::string* fromString){
    double firstIndex = fromString->find_first_of(',');
    double secondIndex = fromString->substr(firstIndex+1).find_first_of(',');
    double lastIndex = fromString->substr(secondIndex+1).find_first_of(',');
    
    this->x = atoi(fromString->substr(0, firstIndex).c_str());
    this->y = atoi(fromString->substr(firstIndex+1, secondIndex).c_str());
    this->z = atoi(fromString->substr(secondIndex+1, lastIndex).c_str());
    this->w = atoi(fromString->substr(lastIndex+1, fromString->length()).c_str());
}


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

double jgl::Quaternion::getYaw(){
    
    double test = x*y + z*w;
    if(test > 0.499){
        return M_PI_2;
    }else if(test < -0.449){
        return -M_PI_2;
    }else{
        return asin(2*test);
    }
}
double jgl::Quaternion::getRoll(){
        double test = x*y + z*w;
    if(test > 0.499){
        return 0;
    }else if(test < -0.449){
        return 0;
    }else{
        return atan2(2.0*(x*w-y*z), 1-2*pow(x,2)-2*pow(z,2));
    }
    
}
double jgl::Quaternion::getPitch(){
    double test = x*y + z*w;
    if(test > 0.499){
        return 2*atan2(x, w);
    }else if(test < -0.449){
        return -2*atan2(x, w);
    }else{
        return atan2(2*(y*w-x*z) , 1 - 2*pow(y,2) - 2*pow(z,2));
    }
}



jgl::Vector3d* jgl::Quaternion::getDirectionVector(){
    return (new jgl::Matrix4d(this))->getRotation();
}



double jgl::Quaternion::getX(){return this->x;}
double jgl::Quaternion::getY(){return this->y;}
double jgl::Quaternion::getZ(){return this->z;}
double jgl::Quaternion::getW(){return this->w;}