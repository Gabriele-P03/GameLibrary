/**
 * TEST SCENE FILE
 * 
 * @file testScene.hpp
 * 
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include "Scene.hpp"
#include "../view/Button.hpp"
#include "../view/TextField.hpp"

namespace jpl{

    class TestScene : public Scene{

        private:

            TextField* textField;
            Button* button;
            TextShader* textShader;
            TextureShader* textureShader;

        public:

            TestScene() : Scene("prova"){

                this->textShader = new TextShader();
                this->textureShader = new TextureShader();

                this->textField = new TextField(300, 300, 500, 20);
                this->textField->background = new Texture("ciao.png");
                this->textField->editable = true;

                button = new Button(0, 0, 100, 100, "(01)");
                button->overMouseTexture = new Texture("ciao.png");
                button->outMouseTexture = new Texture("ciao1.png");
                button->setOnClickListener( [](View* v){
                    //std::cout<<"Button pressed\n";
                } );
            }

            inline virtual void tick() override{
                this->button->tick();
                this->button->render(textureShader, textShader);
                this->textField->tick();
                this->textField->render(textureShader, textShader);
            }
    };
}