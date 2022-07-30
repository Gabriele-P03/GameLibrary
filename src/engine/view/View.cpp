#include "View.hpp"

jpl::View::View(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void jpl::View::setOnClickListener(std::function<void(jpl::View*)> listener){
    this->clickListener = listener;
}

void jpl::View::setOnMouseOverListener(std::function<void(jpl::View*, unsigned int x, unsigned int y)> listener){
    this->mouseOverListener = listener;
}

void jpl::View::setOnMouseOutViewListener(std::function<void(jpl::View*, unsigned int x, unsigned int y)> listener){
    this->mouseOutListener = listener;
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