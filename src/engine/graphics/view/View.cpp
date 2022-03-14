#include "View.hpp"

jpl::View::View(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
}
jpl::View::View(int x, int y) : jpl::View(x, y, 0, 0){}
jpl::View::View() : jpl::View(0, 0, 0, 0){}

int jpl::View::getX(){return this->x;}
int jpl::View::getY(){return this->y;}
int jpl::View::getWidth(){return this->w;}
int jpl::View::getHeight(){return this->h;}

void jpl::View::setX(int x){this->x = x;}
void jpl::View::setY(int y){this->y = y;}
void jpl::View::setWidth(int width){this->w = width;}
void jpl::View::setHeight(int height){this->h = height;}


void jpl::View::tick(){
    
    if(isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
        double x, y;
        getMousePosition(&x, &y);
        y = jpl::WindowSize::INSTANCE.h - y;

        if(x >= this->x && x <= this->w && y >= this->y && y <= this->h){

            //Check if std::function is nullptr, it means that setOnClickListener has not been called
            if(clickListener != nullptr){
                clickListener(this);
            }
        }
    }
}

void jpl::View::render(){
    
    if(this->background != nullptr){
        jpl::TextureShader::TEXTURE_SHADER_DEFAULT->draw(this->background, this->x, this->y, this->w, this->h);
    }
}

void jpl::View::setOnClickListener( std::function <void (jpl::View*)> clickListener){this->clickListener = clickListener;}

void jpl::View::setBackground(jpl::Texture* background){this->background = background;}
