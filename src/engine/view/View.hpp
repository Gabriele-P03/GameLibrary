/**
 * A view is a simple abstraction of a widget
 * e.g. Button, TextField ecc...
 * 
 * @warning If you're gonne including also any Shaders in your sub-class, 
 * remember to include this header file as the last one, this will prevent any
 * conflict about including before GL rather than GLEW
 * 
 *@author Gabriele-P03 
 */

#ifndef VIEW_JPL
#define VIEW_JPL

#include <functional>
#include "../input/mouse/MouseInput.h"

namespace jpl{

    class View{

        protected:

            bool mouseOver; 

            int x, y, w, h;

            std::function<void(View*)> clickListener;
            std::function<void(View*, unsigned int x, unsigned int y)> mouseOverListener;
            std::function<void(View*, unsigned int x, unsigned int y)> mouseOutListener;

        public:

            View(int x, int y, int w, int h);

            /**
             * It should be called on each tick
             * 
             * It does not render anything about the view.
             * It only provides listener on mouse action performed on it
             */
            inline virtual void tick(){
                double xMouse, yMouse;
                getMousePosition(&xMouse, &yMouse);

                if(xMouse >= this->x && xMouse <= this->x + this->w && yMouse >= y && yMouse <= y+h){
                    
                    if(!this->mouseOver){

                        if(this->mouseOverListener)
                            this->mouseOverListener(this, xMouse, yMouse);

                        this->mouseOver = true;
                    }

                    if(isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && mouse_action == GLFW_PRESS && this->clickListener){
                        mouse_action = GLFW_RELEASE;
                        this->clickListener(this);
                    }

                }else{
                    if(this->mouseOver){

                        if(this->mouseOutListener)
                            this->mouseOutListener(this, xMouse, yMouse);
                            
                        this->mouseOver = false;
                    }
                }
            }

            /**
             * Set the On Click Listener object
             * 
             * @param listener method called when mouse clicks on the view
             */
            virtual void setOnClickListener(std::function<void(View*)> listener);

            /**
             * Set the On Mouse Over Listener object
             * 
             * @param listener method called when mouse is over the view
             */
            virtual void setOnMouseOverListener(std::function<void(View*, unsigned int x, unsigned int y)> listener);

            /**
             * Set the On Mouse Out View Listener object
             * 
             * @param listener method called when mouse is out of view. If it is must be called once, 
             * you should use a boolean buffer-value
             */
            virtual void setOnMouseOutViewListener(std::function<void(View*, unsigned int x, unsigned int y)> listener);

            int getX();
            int getY();
            int getW();
            int getH();
    };
}

#endif