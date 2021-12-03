#include "Vector2d.h"


jgl::Vector2d::Vector2d(double x, double y){
    this->x = x;
    this->y = y;
}

jgl::Vector2d::Vector2d() : Vector2d(0, 0){}
jgl::Vector2d::Vector2d(Vector2d* vec2d) : Vector2d( (*vec2d).x, (*vec2d).y ){}
jgl::Vector2d::Vector2d(std::string* fromString){
    this->x = atof(fromString->substr(0, fromString->find(',')).c_str());
    this->y = atof(fromString->substr(fromString->find(',')+1, fromString->size()).c_str());
}

double jgl::Vector2d::getX(){return this->x;}
double jgl::Vector2d::getY(){return this->y;}

void jgl::Vector2d::setX(double x){this->x = x;}
void jgl::Vector2d::setY(double y){this->y = y;}
void jgl::Vector2d::set(Vector2d* vec2d){this->setAll( (*vec2d).x, (*vec2d).y );}
void jgl::Vector2d::setAll(double x, double y){this->x = x; this->y = y;}


void jgl::Vector2d::addX(double x){this->x += x;}
void jgl::Vector2d::addY(double y){this-> y += y;}
void jgl::Vector2d::add(Vector2d* vec2d){this->addX( (*vec2d).x ); this->addY( (*vec2d).y );}
void jgl::Vector2d::addAll(double x, double y){this->addX(x); this->addY(y);}

void jgl::Vector2d::mulX(double x){this->x *= x;}
void jgl::Vector2d::mulY(double y){this->y *= y;}
void jgl::Vector2d::mul(Vector2d* vec2d){this->mulX( (*vec2d).x ); this->mulY( (*vec2d).y );}
void jgl::Vector2d::mulAll(double x, double y){this->mulX(x); this->mulY(y);}



jgl::Vector2d* jgl::Vector2d::cpy(){return new jgl::Vector2d(this->x, this->y);}


jgl::Vector2d* jgl::Vector2d::vrs(){

    jgl::Vector2d* vec = this->cpy();
    double md = this->lenght();

    vec->mulAll(1/md, 1/md);

    return vec;
}

double jgl::Vector2d::dst(jgl::Vector2d* vec2d){
    double deltaX = this->x-vec2d->x;
    double deltaY = this->y-vec2d->y;
    return sqrt( pow(deltaX, 2) + pow(deltaY, 2));
}

double jgl::Vector2d::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) );
}

bool jgl::Vector2d::isNull(){
    return this->lenght() == 0;
}

double jgl::Vector2d::dot(jgl::Vector2d* vec2d){
    return this->x*vec2d->x + this->y*vec2d->y;
}

double jgl::Vector2d::crs(jgl::Vector2d* vec2d){
    return  this->x*vec2d->y - this->y*vec2d->x;
}

double jgl::Vector2d::angleRad(jgl::Vector2d* vec2d){
    double norm = this->lenght();
    double ps = this->dot(vec2d);
    double normParam = vec2d->lenght();
    return acos(ps/(norm*normParam));
}

double jgl::Vector2d::angleGrd(jgl::Vector2d* vec2d){
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
    isNegative(this->x) != isNegative((double)vec2d->x) &&
    isNegative(this->y) != isNegative((double)vec2d->y);
    return flag;
}

bool jgl::Vector2d::acuteAngle(jgl::Vector2d* vec2d){
    double angle = this->dot(vec2d);
    return angle > 0 && angle != 0;
}

bool jgl::Vector2d::obtuseAngle(jgl::Vector2d* vec2d){
    double angle = this->dot(vec2d);
    return angle < 0 && angle != 0;
}

void jgl::Vector2d::rotate(double _rad){
    this->setX( cos(_rad)*this->x - sin(_rad)*this->y );
    this->setY( sin(_rad)*this->x + cos(_rad)*this->y );
}

void jgl::Vector2d::rotateAround(jgl::Vector2d* vec2d, double _rad){
    this->addAll(-vec2d->x, -vec2d->y);
    this->rotate(_rad);
    this->add(vec2d);
}

std::string* jgl::Vector2d::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y));
}

 jgl::Vector2d jgl::Vector2d::xAxis = jgl::Vector2d(1.0, 0.0);
 jgl::Vector2d jgl::Vector2d::yAxis = jgl::Vector2d(0.0, 1.0);