/**
 * A view is a simple abstraction of stuff which can be renderd on window in a 2D context which aren't
 * in gameplay environment. It means that they're buttons, text-input field and so on...
 * 
 * All shaders for rendering views' stuff are in common for every of them as protected static fields
 * 
 * If you're gonna using some views already available, which render text, they had been meant to use
 * default text shader available as public static field @see TextShader
 * Also the texture shader which is used, is the default one
 * 
 * @author Gabriele-P03
 */

#ifndef VIEW_JPL_HPP
#define VIEW_JPL_HPP

#include "../shader/textShader/TextShader.hpp"
#include "../../input/mouse/MouseInput.h"
#include <functional>

namespace jpl{

    class View{

        protected:

            //x,y are bottom-left corner's coords
            //w,h are respectively width and height
            int x, y, w, h;

            View();
            View(int x, int y);
            View(int x, int y, int width, int height);

            std::function <void (View*)> clickListener;

            //It is the background texture
            Texture* background;

        public:

            int getX();
            int getY();
            int getWidth();
            int getHeight();

            void setX(int x);
            void setY(int y);
            void setWidth(int w);
            void setHeight(int h);

            /**
             * Called on every game's tick
             * It checks if player clicks within button's edges.
             * If clicked, its listener is called passing button itselves  
             */ 
            virtual void tick();

            /**
             * Called on tick
             * It renders the view
             */ 
            virtual void render();

            /**
             * Function passed to this method in definition step, will be called once player
             * press the view
             */ 
            void setOnClickListener( std::function <void (View*)> clickListener);

            /**
             * Set the background texture which will be rendered behind the view
             */ 
            void setBackground(Texture* background);
    };
    
} 

#endif
