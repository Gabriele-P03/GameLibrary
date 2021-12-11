#include "Vector2f.h"


jgl::Vector2f::Vector2f(float x, float y){
    this->x = x;
    this->y = y;
}
jgl::Vector2f::Vector2f() : Vector2f(0, 0){}
jgl::Vector2f::Vector2f(Vector2f* vec2f) : Vector2f( (*vec2f).x, (*vec2f).y ){}
jgl::Vector2f::Vector2f(std::string* fromString){
    this->x = atoi(fromString->substr(0, fromString->find(',')).c_str());
    this->y = atoi(fromString->substr(fromString->find(',')+1, fromString->size()).c_str());
}



float jgl::Vector2f::getX(){return this->x;}
float jgl::Vector2f::getY(){return this->y;}



jgl::Vector2f* jgl::Vector2f::setX(float x){this->x = x; return this;}
jgl::Vector2f* jgl::Vector2f::setY(float y){this->y = y; return this;}
jgl::Vector2f* jgl::Vector2f::set(Vector2f* vec2f){this->setAll( (*vec2f).x, (*vec2f).y ); return this;}
jgl::Vector2f* jgl::Vector2f::setAll(float x, float y){this->x = x; this->y = y; return this;}



jgl::Vector2f* jgl::Vector2f::addX(float x){this->x += x; return this;}
jgl::Vector2f* jgl::Vector2f::addY(float y){this-> y += y; return this;}
jgl::Vector2f* jgl::Vector2f::add(Vector2f* vec2f){this->addX( (*vec2f).x ); this->addY( (*vec2f).y ); return this;}
jgl::Vector2f* jgl::Vector2f::addAll(float x, float y){this->addX(x); this->addY(y); return this;}



jgl::Vector2f* jgl::Vector2f::mulX(float x){this->x *= x; return this;}
jgl::Vector2f* jgl::Vector2f::mulY(float y){this->y *= y; return this;}
jgl::Vector2f* jgl::Vector2f::mul(Vector2f* vec2f){this->mulX( (*vec2f).x ); this->mulY( (*vec2f).y ); return this;}
jgl::Vector2f* jgl::Vector2f::mulAll(float x, float y){this->mulX(x); this->mulY(y); return this;}



jgl::Vector2f* jgl::Vector2f::cpy(){return new jgl::Vector2f(this->x, this->y);}



jgl::Vector2f* jgl::Vector2f::vrs(){
    double md = this->lenght();
    this->mulAll(1/md, 1/md);
    return this;
}



double jgl::Vector2f::dst(jgl::Vector2f* vec2f){
    double deltaX = this->x-vec2f->x;
    double deltaY = this->y-vec2f->y;
    return sqrt( pow(deltaX, 2) + pow(deltaY, 2));
}



double jgl::Vector2f::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) );
}



bool jgl::Vector2f::isNull(){
    return this->lenght() == 0;
}



double jgl::Vector2f::dot(jgl::Vector2f* vec2f){
    return this->x*vec2f->x + this->y*vec2f->y;
}



double jgl::Vector2f::crs(jgl::Vector2f* vec2f){
    return  this->x*vec2f->y - this->y*vec2f->x;
}



double jgl::Vector2f::angleRad(jgl::Vector2f* vec2f){
    double norm = this->lenght();
    double ps = this->dot(vec2f);
    double normParam = vec2f->lenght();
    return acos(ps/(norm*normParam));
}



double jgl::Vector2f::angleGrd(jgl::Vector2f* vec2f){
    return this->angleRad(vec2f) * 180 /  M_PI;
}



bool jgl::Vector2f::equals(jgl::Vector2f* vec2f){
    return this->isParallel(vec2f) && this->lenght() == vec2f->lenght();
}



bool jgl::Vector2f::isPerpendicular(jgl::Vector2f* vec2f){
    return this->dot(vec2f) == 0;
}



bool jgl::Vector2f::isParallel(jgl::Vector2f* vec2f){
    return this->crs(vec2f) == 0;
}



bool jgl::Vector2f::sameDirection(jgl::Vector2f* vec2f){
    bool flag = this->crs(vec2f) == 0 && !oppositeDirection(vec2f);
    return flag;
}



bool jgl::Vector2f::oppositeDirection(jgl::Vector2f* vec2f){
    bool flag = this->crs(vec2f) == 0 && 
    isNegative(this->x) != isNegative((double)vec2f->x) &&
    isNegative(this->y) != isNegative((double)vec2f->y);
    return flag;
}



bool jgl::Vector2f::acuteAngle(jgl::Vector2f* vec2f){
    double angle = this->dot(vec2f);
    return angle > 0 && angle != 0;
}



bool jgl::Vector2f::obtuseAngle(jgl::Vector2f* vec2f){
    double angle = this->dot(vec2f);
    return angle < 0 && angle != 0;
}



jgl::Vector2f* jgl::Vector2f::rotate(double _rad){
    double q = std::cos(_rad);
    float x = q*this->x - sin(_rad)*this->y;
    this->setX( x );
    this->setY( sin(_rad)*this->x + cos(_rad)*this->y );
     return this;
}



jgl::Vector2f* jgl::Vector2f::rotateAround(jgl::Vector2f* vec2f, double _rad){
    this->addAll(-vec2f->x, -vec2f->y);
    this->rotate(_rad);
    this->add(vec2f);
     return this;
}



std::string* jgl::Vector2f::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y));
}



jgl::Matrix3d* jgl::Vector2f::getRotationMatrix(){
    return new jgl::Matrix3d(this->angleRad(&jgl::Vector2f::xAxis));
}
jgl::Matrix3d* jgl::Vector2f::getTranslationMatrix(){
    return (new jgl::Matrix3d())->setToTranslation(this->x, this->y);
}
jgl::Matrix3d* jgl::Vector2f::getScalingMatrix(){
    return (new jgl::Matrix3d())->setToScaling(this->x, this->y);
}



 jgl::Vector2f jgl::Vector2f::xAxis = jgl::Vector2f(1, 0);
 jgl::Vector2f jgl::Vector2f::yAxis = jgl::Vector2f(0, 1);