#include "Vector3d.h"

 jgl::Vector3d jgl::Vector3d::xAxis = jgl::Vector3d(1, 0, 0);
 jgl::Vector3d jgl::Vector3d::yAxis = jgl::Vector3d(0, 1, 0);
 jgl::Vector3d jgl::Vector3d::zAxis = jgl::Vector3d(0, 0, 1);

jgl::Vector3d::Vector3d(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
jgl::Vector3d::Vector3d() : Vector3d(0, 0, 0){}
jgl::Vector3d::Vector3d(Vector3d* vec3d) : Vector3d( (*vec3d).x, (*vec3d).y, (*vec3d).z ){}
jgl::Vector3d::Vector3d(std::string* fromString){
    double firstIndex = fromString->find_first_of(','), lastIndex = fromString->find_last_of(',');

    this->x = atoi(fromString->substr(0, firstIndex).c_str());
    this->y = atoi(fromString->substr(firstIndex+1, lastIndex).c_str());
    this->z = atoi(fromString->substr(lastIndex+1, fromString->size()).c_str());
}
jgl::Vector3d::Vector3d(jgl::Matrix4d* mat4d) : jgl::Vector3d(mat4d->getRotation()){}
jgl::Vector3d::Vector3d(jgl::Quaternion* quaternion) : jgl::Vector3d(quaternion->getDirectionVector()){}
//jgl::Vector3d::Vector3d(double yaw, double pitch, double roll){}



double jgl::Vector3d::getX(){return this->x;}
double jgl::Vector3d::getY(){return this->y;}
double jgl::Vector3d::getZ(){return this->z;}



jgl::Vector3d* jgl::Vector3d::setX(double x){this->x = x; return this;}
jgl::Vector3d* jgl::Vector3d::setY(double y){this->y = y; return this;}
jgl::Vector3d* jgl::Vector3d::setZ(double z){this->z = z; return this;}
jgl::Vector3d* jgl::Vector3d::setAll(double x, double y, double z){this->x = x; this->y = y; this->z = z; return this;}
jgl::Vector3d* jgl::Vector3d::set(Vector3d* vec3d){this->setAll( (*vec3d).x, (*vec3d).y, (*vec3d).z ); return this;}



jgl::Vector3d* jgl::Vector3d::addX(double x){this->x += x; return this;}
jgl::Vector3d* jgl::Vector3d::addY(double y){this-> y += y; return this;}
jgl::Vector3d* jgl::Vector3d::addZ(double z){this-> z += z; return this;}
jgl::Vector3d* jgl::Vector3d::add(Vector3d* vec3d){
    this->addX( (*vec3d).x ); 
    this->addY( (*vec3d).y );
    this->addZ( (*vec3d).z );
    return this;
}
jgl::Vector3d* jgl::Vector3d::addAll(double x, double y, double z){
    this->addX(x);
    this->addY(y);
    this->addZ(z);
    return this;
}



jgl::Vector3d* jgl::Vector3d::mulX(double x){this->x *= x; return this;}
jgl::Vector3d* jgl::Vector3d::mulY(double y){this->y *= y; return this;}
jgl::Vector3d* jgl::Vector3d::mulZ(double z){this->z *= z; return this;}
jgl::Vector3d* jgl::Vector3d::mul(Vector3d* vec3d){
    this->mulX( (*vec3d).x );
    this->mulY( (*vec3d).y );
    this->mulZ( (*vec3d).z );
    return this;
}
jgl::Vector3d* jgl::Vector3d::mulAll(double x, double y, double z){this->mulX(x); this->mulY(y); this->mulZ(z); return this;}



jgl::Vector3d* jgl::Vector3d::cpy(){return new jgl::Vector3d(this->x, this->y, this->z); return this;}



jgl::Vector3d* jgl::Vector3d::vrs(){

    double md = this->lenght();
    this->mulAll(1/md, 1/md, 1/md);
    return this;
}



double jgl::Vector3d::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) + pow(this->z, 2));
}



double jgl::Vector3d::dst(jgl::Vector3d* vec3d){
    double deltaX = this->x - vec3d->x;
    double deltaY = this->y - vec3d->y;
    double deltaZ = this->z - vec3d->z;

    return sqrt( deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ );
}



bool jgl::Vector3d::isNull(){
    return this->lenght() == 0;
}



double jgl::Vector3d::dot(jgl::Vector3d* vec3d){
    return this->x*vec3d->x + this->y*vec3d->y + this->z*vec3d->z;
}



jgl::Vector3d* jgl::Vector3d::crs(jgl::Vector3d* vec3d){
    return new jgl::Vector3d(
        this->y*vec3d->z - this->z*vec3d->y,
        this->z*vec3d->x - this->x*vec3d->z,
        this->x*vec3d->y - this->y*vec3d->x 
    );
}



double jgl::Vector3d::angleRad(jgl::Vector3d* vec3d){
    double normFirst = this->lenght();
    double normSecond = vec3d->lenght();

    return acos( this->cpy()->dot(vec3d)/(normFirst*normSecond) );
}



double jgl::Vector3d::angleGrd(jgl::Vector3d* vec3d){
    return toDegree(this->angleRad(vec3d));
}



bool jgl::Vector3d::equals(jgl::Vector3d* vec3d){
    return this->isParallel(vec3d) && this->lenght() == vec3d->lenght();
}



bool jgl::Vector3d::isPerpendicular(jgl::Vector3d* vec3d){
    return this->dot(vec3d) == 0;
}



bool jgl::Vector3d::isParallel(jgl::Vector3d* vec3d){
    return this->crs(vec3d) == 0;
}



bool jgl::Vector3d::sameDirection(jgl::Vector3d* vec3d){
    bool flag = this->crs(vec3d) == 0 && !oppositeDirection(vec3d);
    return flag;
}



bool jgl::Vector3d::oppositeDirection(jgl::Vector3d* vec3d){
    bool flag = this->crs(vec3d) == 0 && 
    isNegative(this->x) != isNegative((double)vec3d->x) &&
    isNegative(this->y) != isNegative((double)vec3d->y);
    return flag;
}



bool jgl::Vector3d::acuteAngle(jgl::Vector3d* vec3d){
    double angle = this->dot(vec3d);
    return angle > 0 && angle != 0;
}



bool jgl::Vector3d::obtuseAngle(jgl::Vector3d* vec3d){
    double angle = this->dot(vec3d);
    return angle < 0 && angle != 0;
}



jgl::Vector3d* jgl::Vector3d::rotate(double _rad, jgl::Vector3d* axis){

    if(axis->x == 1 && axis->y == 0 && axis->z == 0){
        this->setAll(
            this->x,
            cos(_rad)*this->y - sin(_rad)*this->z,
            sin(_rad)*this->y + cos(_rad)*this->z
        );
    }else if(axis->x == 0 && axis->y == 1 && axis->z == 0){
        this->setAll(
            cos(_rad)*this->x + sin(_rad)*this->z,
            this->y,
            sin(_rad)*-this->x + cos(_rad)*this->z
        );
    }else if(axis->x == 0 && axis->y == 0 && axis->z == 1){
        this->setAll(
            cos(_rad)*this->x - sin(_rad)*this->y,
            sin(_rad)*this->x + cos(_rad)*this->y,
            this->z
        );
    }else{
        std::cout<<"Error axis rotation given\n";
        exit(EXIT_FAILURE);
    }

    return this;
}



jgl::Vector3d* jgl::Vector3d::rotateAround(jgl::Vector3d* vec3d, double _rad, jgl::Vector3d* axis){
    this->addAll( -(*vec3d).x, -(*vec3d).y, -(*vec3d).z );
    this->rotate(_rad, axis);
    this->add(vec3d);

    return this;
}



std::string* jgl::Vector3d::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z));
}



jgl::Matrix4d* jgl::Vector3d::getRotationMatrix(){
    return new jgl::Matrix4d(this);
}
jgl::Matrix4d* jgl::Vector3d::getScalingMatrix(){
    return (new jgl::Matrix4d)->setToScale(this);
}
jgl::Matrix4d* jgl::Vector3d::getTranslationMatrix(){
    return (new jgl::Matrix4d)->setToTranslation(this);
}