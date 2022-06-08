/**
 * 
 * A text field is a view which player is able to write in.
 * 
 * @author Gabriele-P03
 */ 

#ifndef TEXTFIELD_JPL_HPP
#define TEXTFIELD_JPL_HPP

#include "../buttons/Button.hpp"
#include "../../../input/key/KeyInput.h"
#include <stdio.h>
#include <curses.h>

namespace jpl{

    class TextField : public Button{

        protected:

            //True when player has clicked on it (writing allowed), otherwise false
            //It is false when player clicks outside, otherwise true 
            bool focused;

            //Allow players to edit the text
            bool editable;

        public:

            TextField(std::string text, int x, int y, int w, int h);
            TextField(int x, int y, int w, int h);


            void setOverlay(Texture* overlay) override;

            virtual void tick() override;
            virtual void render() override;

            bool isFocused();
    };
}

#endif