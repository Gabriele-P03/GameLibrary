#include "Vector3i.h"

 jgl::Vector3i jgl::Vector3i::xAxis = jgl::Vector3i(1, 0, 0);
 jgl::Vector3i jgl::Vector3i::yAxis = jgl::Vector3i(0, 1, 0);
 jgl::Vector3i jgl::Vector3i::zAxis = jgl::Vector3i(0, 0, 1);

jgl::Vector3i::Vector3i(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}
jgl::Vector3i::Vector3i() : Vector3i(0, 0, 0){}
jgl::Vector3i::Vector3i(Vector3i* vec3i) : Vector3i( (*vec3i).x, (*vec3i).y, (*vec3i).z ){}
jgl::Vector3i::Vector3i(std::string* fromString){
    int firstIndex = fromString->find_first_of(','), lastIndex = fromString->find_last_of(',');

    this->x = atoi(fromString->substr(0, firstIndex).c_str());
    this->y = atoi(fromString->substr(firstIndex+1, lastIndex).c_str());
    this->z = atoi(fromString->substr(lastIndex+1, fromString->size()).c_str());
}



int jgl::Vector3i::getX(){return this->x;}
int jgl::Vector3i::getY(){return this->y;}
int jgl::Vector3i::getZ(){return this->z;}



jgl::Vector3i* jgl::Vector3i::setX(int x){this->x = x; return this;}
jgl::Vector3i* jgl::Vector3i::setY(int y){this->y = y; return this;}
jgl::Vector3i* jgl::Vector3i::setZ(int z){this->z = z; return this;}
jgl::Vector3i* jgl::Vector3i::setAll(int x, int y, int z){this->x = x; this->y = y; this->z = z; return this;}
jgl::Vector3i* jgl::Vector3i::set(Vector3i* vec3i){this->setAll( (*vec3i).x, (*vec3i).y, (*vec3i).z ); return this;}



jgl::Vector3i* jgl::Vector3i::addX(int x){this->x += x; return this;}
jgl::Vector3i* jgl::Vector3i::addY(int y){this-> y += y; return this;}
jgl::Vector3i* jgl::Vector3i::addZ(int z){this-> z += z; return this;}
jgl::Vector3i* jgl::Vector3i::add(Vector3i* vec3i){
    this->addX( (*vec3i).x ); 
    this->addY( (*vec3i).y );
    this->addZ( (*vec3i).z );
    return this;
}
jgl::Vector3i* jgl::Vector3i::addAll(int x, int y, int z){
    this->addX(x);
    this->addY(y);
    this->addZ(z);
    return this;
}



jgl::Vector3i* jgl::Vector3i::mulX(int x){this->x *= x; return this;}
jgl::Vector3i* jgl::Vector3i::mulY(int y){this->y *= y; return this;}
jgl::Vector3i* jgl::Vector3i::mulZ(int z){this->z *= z; return this;}
jgl::Vector3i* jgl::Vector3i::mul(Vector3i* vec3i){
    this->mulX( (*vec3i).x );
    this->mulY( (*vec3i).y );
    this->mulZ( (*vec3i).z );
    return this;
}
jgl::Vector3i* jgl::Vector3i::mulAll(int x, int y, int z){this->mulX(x); this->mulY(y); this->mulZ(z); return this;}



jgl::Vector3i* jgl::Vector3i::cpy(){return new jgl::Vector3i(this->x, this->y, this->z); return this;}



jgl::Vector3i* jgl::Vector3i::vrs(){

    double md = this->lenght();
    this->mulAll(1/md, 1/md, 1/md);
    return this;
}



double jgl::Vector3i::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) + pow(this->z, 2));
}



double jgl::Vector3i::dst(jgl::Vector3i* vec3i){
    double deltaX = this->x - vec3i->x;
    double deltaY = this->y - vec3i->y;
    double deltaZ = this->z - vec3i->z;

    return sqrt( deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ );
}



bool jgl::Vector3i::isNull(){
    return this->lenght() == 0;
}



double jgl::Vector3i::dot(jgl::Vector3i* vec3i){
    return this->x*vec3i->x + this->y*vec3i->y + this->z*vec3i->z;
}



jgl::Vector3i* jgl::Vector3i::crs(jgl::Vector3i* vec3i){
    return new jgl::Vector3i(
        this->y*vec3i->z - this->z*vec3i->y,
        this->z*vec3i->x - this->x*vec3i->z,
        this->x*vec3i->y - this->y*vec3i->x 
    );
}



double jgl::Vector3i::angleRad(jgl::Vector3i* vec3i){
    double normFirst = this->lenght();
    double normSecond = vec3i->lenght();

    return acos( this->cpy()->dot(vec3i)/(normFirst*normSecond) );
}



double jgl::Vector3i::angleGrd(jgl::Vector3i* vec3i){
    return toDegree(this->angleRad(vec3i));
}



bool jgl::Vector3i::equals(jgl::Vector3i* vec3i){
    return this->isParallel(vec3i) && this->lenght() == vec3i->lenght();
}



bool jgl::Vector3i::isPerpendicular(jgl::Vector3i* vec3i){
    return this->dot(vec3i) == 0;
}



bool jgl::Vector3i::isParallel(jgl::Vector3i* vec3i){
    return this->crs(vec3i) == 0;
}



bool jgl::Vector3i::sameDirection(jgl::Vector3i* vec3i){
    bool flag = this->crs(vec3i) == 0 && !oppositeDirection(vec3i);
    return flag;
}



bool jgl::Vector3i::oppositeDirection(jgl::Vector3i* vec3i){
    bool flag = this->crs(vec3i) == 0 && 
    isNegative(this->x) != isNegative((double)vec3i->x) &&
    isNegative(this->y) != isNegative((double)vec3i->y);
    return flag;
}



bool jgl::Vector3i::acuteAngle(jgl::Vector3i* vec3i){
    double angle = this->dot(vec3i);
    return angle > 0 && angle != 0;
}



bool jgl::Vector3i::obtuseAngle(jgl::Vector3i* vec3i){
    double angle = this->dot(vec3i);
    return angle < 0 && angle != 0;
}



jgl::Vector3i* jgl::Vector3i::rotate(double _rad, jgl::Vector3i* axis){

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



jgl::Vector3i* jgl::Vector3i::rotateAround(jgl::Vector3i* vec3i, double _rad, jgl::Vector3i* axis){
    this->addAll( -(*vec3i).x, -(*vec3i).y, -(*vec3i).z );
    this->rotate(_rad, axis);
    this->add(vec3i);

    return this;
}



std::string* jgl::Vector3i::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z));
}


