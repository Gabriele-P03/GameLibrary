#include "Vector2i.h"


jgl::Vector2i::Vector2i(int x, int y){
    this->x = x;
    this->y = y;
}

jgl::Vector2i::Vector2i() : Vector2i(0, 0){}
jgl::Vector2i::Vector2i(Vector2i* vec2i) : Vector2i( (*vec2i).x, (*vec2i).y ){}
jgl::Vector2i::Vector2i(std::string* fromString){
    this->x = atoi(fromString->substr(0, fromString->find(',')).c_str());
    this->y = atoi(fromString->substr(fromString->find(',')+1, fromString->size()).c_str());
}

int jgl::Vector2i::getX(){return this->x;}
int jgl::Vector2i::getY(){return this->y;}

void jgl::Vector2i::setX(int x){this->x = x;}
void jgl::Vector2i::setY(int y){this->y = y;}
void jgl::Vector2i::set(Vector2i* vec2i){this->setAll( (*vec2i).x, (*vec2i).y );}
void jgl::Vector2i::setAll(int x, int y){this->x = x; this->y = y;}


void jgl::Vector2i::addX(int x){this->x += x;}
void jgl::Vector2i::addY(int y){this-> y += y;}
void jgl::Vector2i::add(Vector2i* vec2i){this->addX( (*vec2i).x ); this->addY( (*vec2i).y );}
void jgl::Vector2i::addAll(int x, int y){this->addX(x); this->addY(y);}

void jgl::Vector2i::mulX(int x){this->x *= x;}
void jgl::Vector2i::mulY(int y){this->y *= y;}
void jgl::Vector2i::mul(Vector2i* vec2i){this->mulX( (*vec2i).x ); this->mulY( (*vec2i).y );}
void jgl::Vector2i::mulAll(int x, int y){this->mulX(x); this->mulY(y);}



jgl::Vector2i* jgl::Vector2i::cpy(){return new jgl::Vector2i(this->x, this->y);}

jgl::Vector2i* jgl::Vector2i::vrs(){

    jgl::Vector2i* vec = this->cpy();
    double md = this->lenght();

    vec->mulAll(1/md, 1/md);

    return vec;
}

double jgl::Vector2i::dst(jgl::Vector2i* vec2i){
    double deltaX = this->x-vec2i->x;
    double deltaY = this->y-vec2i->y;
    return sqrt( pow(deltaX, 2) + pow(deltaY, 2));
}

double jgl::Vector2i::lenght(){
    return sqrt( pow(this->x, 2) + pow(this->y,2) );
}

bool jgl::Vector2i::isNull(){
    return this->lenght() == 0;
}

double jgl::Vector2i::dot(jgl::Vector2i* vec2i){
    return this->x*vec2i->x + this->y*vec2i->y;
}

double jgl::Vector2i::crs(jgl::Vector2i* vec2i){
    return  this->x*vec2i->y - this->y*vec2i->x;
}

double jgl::Vector2i::angleRad(jgl::Vector2i* vec2i){
    double norm = this->lenght();
    double ps = this->dot(vec2i);
    double normParam = vec2i->lenght();
    return acos(ps/(norm*normParam));
}

double jgl::Vector2i::angleGrd(jgl::Vector2i* vec2i){
    return this->angleRad(vec2i) * 180 /  M_PI;
}

bool jgl::Vector2i::equals(jgl::Vector2i* vec2i){
    return this->isParallel(vec2i) && this->lenght() == vec2i->lenght();
}

bool jgl::Vector2i::isPerpendicular(jgl::Vector2i* vec2i){
    return this->dot(vec2i) == 0;
}

bool jgl::Vector2i::isParallel(jgl::Vector2i* vec2i){
    return this->crs(vec2i) == 0;
}


bool jgl::Vector2i::sameDirection(jgl::Vector2i* vec2i){
    bool flag = this->crs(vec2i) == 0 && !oppositeDirection(vec2i);
    return flag;
}

bool jgl::Vector2i::oppositeDirection(jgl::Vector2i* vec2i){
    bool flag = this->crs(vec2i) == 0 && 
    isNegative(this->x) != isNegative((double)vec2i->x) &&
    isNegative(this->y) != isNegative((double)vec2i->y);
    return flag;
}

bool jgl::Vector2i::acuteAngle(jgl::Vector2i* vec2i){
    double angle = this->dot(vec2i);
    return angle > 0 && angle != 0;
}

bool jgl::Vector2i::obtuseAngle(jgl::Vector2i* vec2i){
    double angle = this->dot(vec2i);
    return angle < 0 && angle != 0;
}

void jgl::Vector2i::rotate(double _rad){
    double q = std::cos(_rad);
    float x = q*this->x - sin(_rad)*this->y;
    this->setX( x );
    this->setY( sin(_rad)*this->x + cos(_rad)*this->y );
}

void jgl::Vector2i::rotateAround(jgl::Vector2i* vec2i, double _rad){
    this->addAll(-vec2i->x, -vec2i->y);
    this->rotate(_rad);
    this->add(vec2i);
}

std::string* jgl::Vector2i::toString(){  
    return new std::string( std::to_string(this->x) + ", " + std::to_string(this->y));
}

 jgl::Vector2i jgl::Vector2i::xAxis = jgl::Vector2i(1, 0);
 jgl::Vector2i jgl::Vector2i::yAxis = jgl::Vector2i(0, 1);