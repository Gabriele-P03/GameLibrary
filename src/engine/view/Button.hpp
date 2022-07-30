/**
 * This is a simple abstraction of a button, already containing 
 * two textures (out and over mouse both)
 * 
 * @author Gabriele-P03
 */

#ifndef BUTTON_JPL
#define BUTTON_JPL


#include "../graphics/texture/Texture.hpp"
#include "../graphics/shader/TextShader.hpp"
#include "../graphics/shader/TextureShader.hpp"

//Including it after shaders. Read View doc!
#include "View.hpp"
#include <string>
#include <iostream>

namespace jpl{
    
    class Button : public View{


        public:

            Button(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            Button(unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string text);

    
            std::string text;
            Texture* overMouseTexture, *outMouseTexture;

            inline virtual void render(TextureShader* textureShader, TextShader* textShader){
                
                if(overMouseTexture != nullptr && outMouseTexture != nullptr){

                    textureShader->draw(
                        this->mouseOver ? this->overMouseTexture : outMouseTexture,
                        this->x, 
                        this->y, 
                        0.0f, 
                        this->w, 
                        this->h, 
                        0.0f, 
                        0.0f, 
                        (this->mouseOver ? this->overMouseTexture->getWidth() : outMouseTexture->getWidth()),
                        (this->mouseOver ? this->overMouseTexture->getHeight() : outMouseTexture->getHeight())
                    );
                }
            }

            inline virtual void tick() override {
                View::tick();
                
                /*
                    It must be called by a SceneManager due to its need of a texture shader and text one
                */
                //this->render();
            }
    };
} 


#endif