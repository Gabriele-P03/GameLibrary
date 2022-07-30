#include "Button.hpp"

jpl::Button::Button(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
    : jpl::View(x, y, w, h){}
jpl::Button::Button(unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string text)
    : jpl::Button(x, y, w, h){

        this->text = text;
}
