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

        public:
            Button(int x, int y, int width, int height);
            Button(int x, int y);
            Button();

            void tick() override;
            void render() override;

            virtual void setText(std::string* text);
            std::string* getText();
    };
}

#endif