#include "View.hpp"

jpl::View::View(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void jpl::View::setOnClickListener(std::function<void(jpl::View*)> listener){
    this->listener = listener;
}

int jpl::View::getX(){
    return this->x;
}
int jpl::View::getY(){
    return this->y;
}
int jpl::View::getW(){
    return this->w;
}
int jpl::View::getH(){
    return this->h;
}