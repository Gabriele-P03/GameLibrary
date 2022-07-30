/**
 * A TextField is a field which can render text
 * 
 * Setting the editable boolean, programmer can able the player to type in it.
 * Also, if the text field is gonna be used only for rendering text (not to type in),
 * you can avoid to call TextField#tick(), since it is used to listen keyboard.
 * But if your textfield has a listener, despite it is uneditable, you must call it 
 * 
 * @author Gabriele-P03 
 */

#ifndef TEXTFIELD_JPL
#define TEXTFIELD_JPL

#include "../graphics/texture/Texture.hpp"
#include "../graphics/shader/TextShader.hpp"
#include "../graphics/shader/TextureShader.hpp"

//Including it after shaders. Read View doc!
#include "View.hpp"
#include <string>

#ifdef __linux__
    #include <ncurses.h>
#elif _WIN32
    #include <conio.h>
#endif

namespace jpl{
    
    class TextField : public View{

        private:
            //Contains if the player has pressed inside the text field in order to get key presses
            bool focus;


        public:

            TextField(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            TextField(unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string text);

            bool editable;
    
            std::string text;
            Texture* background;

            inline virtual void render(TextureShader* textureShader, TextShader* textShader){
                
                if(background != nullptr){

                    textureShader->draw(
                        this->background,
                        this->x, 
                        this->y, 
                        0.0f, 
                        this->w, 
                        this->h, 
                        0.0f, 
                        0.0f, 
                        background->getWidth(),
                        background->getHeight()
                    );
                }

                if(!this->text.empty()){

                    int firstLetter = text.size() - (int)(this->w/textShader->getFontSize());
                    textShader->render(text.substr(firstLetter > 0 ? firstLetter : 0), this->x, this->y, 0.0f, textShader->getFontSize(), this->h);
                }
            }

            inline virtual void tick() override {
                double xMouse, yMouse;
                getMousePosition(&xMouse, &yMouse);

                //Check for mouse button pressing 
                if(isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){

                    //If mouse is inside the box
                    if(xMouse >= this->x && xMouse <= this->x + this->w && yMouse >= y && yMouse <= y+h){
                        
                        if(!this->mouseOver){

                            if(this->mouseOverListener)
                                this->mouseOverListener(this, xMouse, yMouse);

                            this->mouseOver = true;
                        }

                        if(mouse_action == GLFW_PRESS ){

                            mouse_action = GLFW_RELEASE;
                            this->focus = true;

                            if(this->clickListener)
                                this->clickListener(this);
                        }

                    }else{
                        if(this->mouseOver){

                            if(this->mouseOutListener)
                                this->mouseOutListener(this, xMouse, yMouse);
                                
                            this->mouseOver = false;
                        }

                        this->focus = false;
                    }
                }

                if(focus && editable){
                    if(codepoint >= 32 && codepoint <= 126){
                        this->text += char(codepoint);
                        codepoint = 0;
                    }else if(key_buffer == GLFW_KEY_BACKSPACE && action_buffer == GLFW_PRESS){
                        if(!this->text.empty())
                            this->text.erase(this->text.end()-1);

                        key_buffer = -1;
                        action_buffer = GLFW_RELEASE;
                    }
                }
            }
    };
} 

#endif