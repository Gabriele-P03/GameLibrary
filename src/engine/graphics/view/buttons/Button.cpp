#include "Button.hpp"

jpl::Button::Button(int x, int y, int width, int height) : jpl::View(x, y, width, height){
    this->overlay = nullptr;
}
jpl::Button::Button(int x, int y) : jpl::Button(x, y, 0, 0){}
jpl::Button::Button() : jpl::Button(0, 0, 0, 0){}

void jpl::Button::tick(){
    
    if(this->overlay == nullptr){
        jpl::View::tick();
    }else{
        double x, y;
        getMousePosition(&x, &y);
        y = jpl::WindowSize::INSTANCE.h - y;

        if(x >= this->x && x <= this->w && y >= this->y && y <= this->h){
            jpl::TextureShader::TEXTURE_SHADER_DEFAULT->draw(this->overlay, this->x, this->y, this->w, this->h);
            if(isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
                this->clickListener(this);
            }
        }
    }
}

void jpl::Button::render(){
    jpl::View::render();
    this->tick();
    this->renderText();
}

void jpl::Button::renderText(){
    if(this->text != nullptr )
        if(this->text->length() > 0)
            jpl::TextShader::TEXT_SHADER_DEFAULT->render(this->text, this->x, this->y);           
}

void jpl::Button::setText(std::string text){
    this->text = new std::string(text);
}

std::string* jpl::Button::getText(){
    return new std::string(*this->text);
}

void jpl::Button::setOverlay(Texture* overlay){ this->overlay = overlay;}