#include "TextField.hpp"

jpl::TextField::TextField(std::string text, int x, int y, int w, int h) : jpl::Button(x, y, w, h){
    this->text = new std::string(text);
    this->editable = true;
}
jpl::TextField::TextField(int x, int y, int w, int h) : jpl::TextField("", x, y, w, h){}


void jpl::TextField::tick(){

    if(isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
        double x, y;
        getMousePosition(&x, &y);
        y = jpl::WindowSize::INSTANCE.h - y;
        this->focused = (x >= this->x && x <= this->w && y >= this->y && y <= this->h);
    }

    if(this->focused){
        int tmp = key_buffer;
        if(action_buffer == 1 && text != nullptr){
            if(tmp >= 32 && tmp <= 127){
                this->text->insert(this->text->length(), 1, (char)tmp);
                key_buffer = -1;
            }else if(tmp == 259){
                if(text->length() > 0){
                    this->text->pop_back();
                    key_buffer = -1;
                }
            }
        }
    }
}

void jpl::TextField::render(){
    jpl::TextureShader::TEXTURE_SHADER_DEFAULT->draw(this->background, this->x, this->y, this->w, this->h);
    
    if(this->editable)
        this->tick();
    
    this->renderText();
}


bool jpl::TextField::isFocused(){return this->focused;}

void jpl::TextField::setOverlay(jpl::Texture* overlay){}