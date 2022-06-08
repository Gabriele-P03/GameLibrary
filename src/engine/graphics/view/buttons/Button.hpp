/**
 * A button is a clickable view available for GUI.
 */ 

#ifndef BUTTON_JPL_HPP
#define BUTTON_JPL_HPP

#include "../View.hpp"

namespace jpl{

    class Button : public View{

        protected:

            std::string* text;

            /**
             * If you wish to render text with another font or another shader program,
             * just override this method in a Button's child, using you own shader.
             * It is called by Button::render()
             */ 
            virtual void renderText();

            /**
             * This is the texture which will be rendered when cursor is above the button
             * If you don't wanna any rendering overlay, just do not call its setter
             */ 
            Texture* overlay;

        public:
            Button(int x, int y, int width, int height);
            Button(int x, int y);
            Button();

            virtual void tick() override;
            virtual void render() override;

            void setText(std::string text);
            std::string* getText();

            virtual void setOverlay(Texture* overlay);
    };
}

#endif