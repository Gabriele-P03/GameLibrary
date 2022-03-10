/**
 * A view is a simple abstraction of stuff which can be renderd on window in a 2D context
 * All shaders for rendering views' stuff are in common for every of them as protected static fields
 * 
 * Some views may not need TextShader therefore it won't be initialized via View's constructor.
 * Then, if you're gonna makin' your own view and you need it, remember to initialize it.
 * It will be initialized via Button's one ecc...
 * 
 * @author
 */

#ifndef VIEW_JPL_HPP
#define VIEW_JPL_HPP

#include "../../input/mouse/MouseInput.h"
#include <functional>
#include "../shader/textShader/TextShader.hpp"

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

            static TextShader* textShader;  //Used for rendering button's text
            static TextureShader* textureShader;    //Used for rendering button's background texture 

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
    };
    
} 

#endif
