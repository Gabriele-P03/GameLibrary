#include "TextField.hpp"

jpl::TextField::TextField(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
    : jpl::View(x, y, w, h){
        this->focus = false;
        this->background = nullptr;
    }
jpl::TextField::TextField(unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string text)
    : jpl::TextField(x, y, w, h){

        this->text = text;
}
