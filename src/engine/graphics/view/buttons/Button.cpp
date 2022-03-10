#include "Button.hpp"

jpl::Button::Button(int x, int y, int width, int height) : jpl::View(x, y, width, height){
    this->textShader = new jpl::TextShader();
}
jpl::Button::Button(int x, int y) : jpl::Button(x, y, 0, 0){}
jpl::Button::Button() : jpl::Button(0, 0, 0, 0){}

void jpl::Button::tick(){
    jpl::View::tick();
}

void jpl::Button::render(){
    jpl::View::render();
    this->textShader->render(this->text, this->x, this->y);
}

void jpl::Button::setText(std::string* text){
    this->text = text;
}

std::string* jpl::Button::getText(){
    return new std::string(*this->text);
}