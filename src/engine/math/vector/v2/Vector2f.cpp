#include "Vector2f.h"


jgl::Vector2d::Vector2d(float x, float y){
    this->x = x;
    this->y = y;
}
jgl::Vector2d::Vector2d() : Vector2d(0, 0){}
jgl::Vector2d::Vector2d(Vector2d* vec2d) : Vector2d( (*vec2d).x, (*vec2d).y ){}
jgl::Vector2d::Vector2d(std::string* fromString){
    this->x = atoi(fromString->substr(0, fromString->find(',')).c_str());
    this->y = atoi(fromString->substr(fromString->find(',')+1, fromString->size()).c_str());
}



float jgl::Vector2d::getX(){return this->x;}
float jgl::Vector2d::getY(){return this->y;}



jgl::Vector2d* jgl::Vector2d::setX(float x){this->x = x; return this;}
jgl::Vector2d* jgl::Vector2d::setY(float y){this->y = y; return this;}
jgl::Vector2d* jgl::Vector2d::set(Vector2d* vec2d){this->setAll( (*vec2d).x, (*vec2d).y ); return this;}
jgl::Vector2d* jgl::Vector2d::setAll(float x, float y){this->x = x; this->y = y; return this;}



jgl::Vector2d* jgl::Vector2d::addX(float x){this->x += x; return this;}
jgl::Vector2d* jgl::Vector2d::addY(float y){this-> y += y; return this;}
jgl::Vector2d* jgl::Vector2d::add(Vector2d* vec2d){this->addX( (*vec2d).x ); this->addY( (*vec2d).y ); return this;}
jgl::Vector2d* jgl::Vector2d::addAll(float x, float y){this->addX(x); this->addY(y); return this;}



jgl::Vector2d* jgl::Vector2d::mulX(float x){this->x *= x; return this;}
jgl::Vector2d* jgl::Vector2d::mulY(float y){this->y *= y; return this;}
jgl::Vector2d* jgl::Vector2d::mul(Vector2d* vec2d){this->mulX( (*vec2d).x ); this->mulY( (*vec2d).y ); return this;}
jgl::Vector2d* jgl::Vector2d::mulAll(float x, float y){this->mulX(x); this->mulY(y); return this;}



jgl::Vector2d* jgl::Vector2d::cpy(){return new jgl::Vector2d(this->x, this->y);}



jgl::Vector2d* jgl::Vector2d::vrs(){
    float md = this->lenght();
    this->mulAll(1/md, 1/md);
    return this;
}



float jgl::Vector2d::dst(jgl::Vector2d* vec2d){
    float deltaX = this->x-vec2d->x;
    float deltaY = this->y-vec2d->y;
    return sqrt( pow(deltaX, 2) + pow(deltaY, 2));
}



float jgl::Vector2d::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) );
}



bool jgl::Vector2d::isNull(){
    return this->lenght() == 0;
}



float jgl::Vector2d::dot(jgl::Vector2d* vec2d){
    return this->x*vec2d->x + this->y*vec2d->y;
}



float jgl::Vector2d::crs(jgl::Vector2d* vec2d){
    return  this->x*vec2d->y - this->y*vec2d->x;
}



float jgl::Vector2d::angleRad(jgl::Vector2d* vec2d){
    float norm = this->lenght();
    float ps = this->dot(vec2d);
    float normParam = vec2d->lenght();
    return acos(ps/(norm*normParam));
}



float jgl::Vector2d::angleGrd(jgl::Vector2d* vec2d){
    return this->angleRad(vec2d) * 180 /  M_PI;
}



bool jgl::Vector2d::equals(jgl::Vector2d* vec2d){
    return this->isParallel(vec2d) && this->lenght() == vec2d->lenght();
}



bool jgl::Vector2d::isPerpendicular(jgl::Vector2d* vec2d){
    return this->dot(vec2d) == 0;
}



bool jgl::Vector2d::isParallel(jgl::Vector2d* vec2d){
    return this->crs(vec2d) == 0;
}



bool jgl::Vector2d::sameDirection(jgl::Vector2d* vec2d){
    bool flag = this->crs(vec2d) == 0 && !oppositeDirection(vec2d);
    return flag;
}



bool jgl::Vector2d::oppositeDirection(jgl::Vector2d* vec2d){
    bool flag = this->crs(vec2d) == 0 && 
    isNegative(this->x) != isNegative((float)vec2d->x) &&
    isNegative(this->y) != isNegative((float)vec2d->y);
    return flag;
}



bool jgl::Vector2d::acuteAngle(jgl::Vector2d* vec2d){
    float angle = this->dot(vec2d);
    return angle > 0 && angle != 0;
}



bool jgl::Vector2d::obtuseAngle(jgl::Vector2d* vec2d){
    float angle = this->dot(vec2d);
    return angle < 0 && angle != 0;
}



jgl::Vector2d* jgl::Vector2d::rotate(float _rad){
    float q = std::cos(_rad);
    float x = q*this->x - sin(_rad)*this->y;
    this->setX( x );
    this->setY( sin(_rad)*this->x + cos(_rad)*this->y );
     return this;
}



jgl::Vector2d* jgl::Vector2d::rotateAround(jgl::Vector2d* vec2d, float _rad){
    this->addAll(-vec2d->x, -vec2d->y);
    this->rotate(_rad);
    this->add(vec2d);
     return this;
}



std::string* jgl::Vector2d::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y));
}



jgl::Matrix3* jgl::Vector2d::getRotationMatrix(){
    return new jgl::Matrix3(this->angleRad(&jgl::Vector2d::xAxis));
}
jgl::Matrix3* jgl::Vector2d::getTranslationMatrix(){
    return (new jgl::Matrix3())->setToTranslation(this->x, this->y);
}
jgl::Matrix3* jgl::Vector2d::getScalingMatrix(){
    return (new jgl::Matrix3())->setToScaling(this->x, this->y);
}




 jgl::Vector2d jgl::Vector2d::xAxis = jgl::Vector2d(1, 0);
 jgl::Vector2d jgl::Vector2d::yAxis = jgl::Vector2d(0, 1);