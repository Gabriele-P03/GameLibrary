#include "Vector3f.h"

 jgl::Vector3f jgl::Vector3f::xAxis = jgl::Vector3f(1, 0, 0);
 jgl::Vector3f jgl::Vector3f::yAxis = jgl::Vector3f(0, 1, 0);
 jgl::Vector3f jgl::Vector3f::zAxis = jgl::Vector3f(0, 0, 1);

jgl::Vector3f::Vector3f(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
jgl::Vector3f::Vector3f() : Vector3f(0, 0, 0){}
jgl::Vector3f::Vector3f(Vector3f* vec3f) : Vector3f( (*vec3f).x, (*vec3f).y, (*vec3f).z ){}
jgl::Vector3f::Vector3f(std::string* fromString){
    float firstIndex = fromString->find_first_of(','), lastIndex = fromString->find_last_of(',');

    this->x = atoi(fromString->substr(0, firstIndex).c_str());
    this->y = atoi(fromString->substr(firstIndex+1, lastIndex).c_str());
    this->z = atoi(fromString->substr(lastIndex+1, fromString->size()).c_str());
}



float jgl::Vector3f::getX(){return this->x;}
float jgl::Vector3f::getY(){return this->y;}
float jgl::Vector3f::getZ(){return this->z;}



jgl::Vector3f* jgl::Vector3f::setX(float x){this->x = x; return this;}
jgl::Vector3f* jgl::Vector3f::setY(float y){this->y = y; return this;}
jgl::Vector3f* jgl::Vector3f::setZ(float z){this->z = z; return this;}
jgl::Vector3f* jgl::Vector3f::setAll(float x, float y, float z){this->x = x; this->y = y; this->z = z; return this;}
jgl::Vector3f* jgl::Vector3f::set(Vector3f* vec3f){this->setAll( (*vec3f).x, (*vec3f).y, (*vec3f).z ); return this;}



jgl::Vector3f* jgl::Vector3f::addX(float x){this->x += x; return this;}
jgl::Vector3f* jgl::Vector3f::addY(float y){this-> y += y; return this;}
jgl::Vector3f* jgl::Vector3f::addZ(float z){this-> z += z; return this;}
jgl::Vector3f* jgl::Vector3f::add(Vector3f* vec3f){
    this->addX( (*vec3f).x ); 
    this->addY( (*vec3f).y );
    this->addZ( (*vec3f).z );
    return this;
}
jgl::Vector3f* jgl::Vector3f::addAll(float x, float y, float z){
    this->addX(x);
    this->addY(y);
    this->addZ(z);
    return this;
}



jgl::Vector3f* jgl::Vector3f::mulX(float x){this->x *= x; return this;}
jgl::Vector3f* jgl::Vector3f::mulY(float y){this->y *= y; return this;}
jgl::Vector3f* jgl::Vector3f::mulZ(float z){this->z *= z; return this;}
jgl::Vector3f* jgl::Vector3f::mul(Vector3f* vec3f){
    this->mulX( (*vec3f).x );
    this->mulY( (*vec3f).y );
    this->mulZ( (*vec3f).z );
    return this;
}
jgl::Vector3f* jgl::Vector3f::mulAll(float x, float y, float z){this->mulX(x); this->mulY(y); this->mulZ(z); return this;}



jgl::Vector3f* jgl::Vector3f::cpy(){return new jgl::Vector3f(this->x, this->y, this->z); return this;}



jgl::Vector3f* jgl::Vector3f::vrs(){

    double md = this->lenght();
    this->mulAll(1/md, 1/md, 1/md);
    return this;
}



double jgl::Vector3f::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) + pow(this->z, 2));
}



double jgl::Vector3f::dst(jgl::Vector3f* vec3f){
    double deltaX = this->x - vec3f->x;
    double deltaY = this->y - vec3f->y;
    double deltaZ = this->z - vec3f->z;

    return sqrt( deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ );
}



bool jgl::Vector3f::isNull(){
    return this->lenght() == 0;
}



double jgl::Vector3f::dot(jgl::Vector3f* vec3f){
    return this->x*vec3f->x + this->y*vec3f->y + this->z*vec3f->z;
}



jgl::Vector3f* jgl::Vector3f::crs(jgl::Vector3f* vec3f){
    return new jgl::Vector3f(
        this->y*vec3f->z - this->z*vec3f->y,
        this->z*vec3f->x - this->x*vec3f->z,
        this->x*vec3f->y - this->y*vec3f->x 
    );
}



double jgl::Vector3f::angleRad(jgl::Vector3f* vec3f){
    double normFirst = this->lenght();
    double normSecond = vec3f->lenght();

    return acos( this->cpy()->dot(vec3f)/(normFirst*normSecond) );
}



double jgl::Vector3f::angleGrd(jgl::Vector3f* vec3f){
    return toDegree(this->angleRad(vec3f));
}



bool jgl::Vector3f::equals(jgl::Vector3f* vec3f){
    return this->isParallel(vec3f) && this->lenght() == vec3f->lenght();
}



bool jgl::Vector3f::isPerpendicular(jgl::Vector3f* vec3f){
    return this->dot(vec3f) == 0;
}



bool jgl::Vector3f::isParallel(jgl::Vector3f* vec3f){
    return this->crs(vec3f) == 0;
}



bool jgl::Vector3f::sameDirection(jgl::Vector3f* vec3f){
    bool flag = this->crs(vec3f) == 0 && !oppositeDirection(vec3f);
    return flag;
}



bool jgl::Vector3f::oppositeDirection(jgl::Vector3f* vec3f){
    bool flag = this->crs(vec3f) == 0 && 
    isNegative(this->x) != isNegative((double)vec3f->x) &&
    isNegative(this->y) != isNegative((double)vec3f->y);
    return flag;
}



bool jgl::Vector3f::acuteAngle(jgl::Vector3f* vec3f){
    double angle = this->dot(vec3f);
    return angle > 0 && angle != 0;
}



bool jgl::Vector3f::obtuseAngle(jgl::Vector3f* vec3f){
    double angle = this->dot(vec3f);
    return angle < 0 && angle != 0;
}



jgl::Vector3f* jgl::Vector3f::rotate(double _rad, jgl::Vector3f* axis){

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



jgl::Vector3f* jgl::Vector3f::rotateAround(jgl::Vector3f* vec3f, double _rad, jgl::Vector3f* axis){
    this->addAll( -(*vec3f).x, -(*vec3f).y, -(*vec3f).z );
    this->rotate(_rad, axis);
    this->add(vec3f);

    return this;
}



std::string* jgl::Vector3f::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z));
}


