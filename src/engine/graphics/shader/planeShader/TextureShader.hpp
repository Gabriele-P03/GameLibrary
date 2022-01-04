/**
 * Draw texture in 2D case. 2D is refered to texture, not to rotation. You can rotate it around Y/X axis, too.
 * This shader has own rotation matrix which you can apply your transformations on
 *
 * A lots of drawing methods are available. Check their doc to get more info. 
 * Anyway, even if OpenGl'coords range is [-1;+1] with center [0;0] (window center), you don't need to care about it.
 * Once you invoke a more detailed method (coords where render textute), it will calculate coords in range [-1;+1].
 * WARNING: This shader NOT check if coords are in range of screen width-height
 * 
 * @author Gabriele-P03
 */ 

#ifndef TEXTURESHADER_HPP
#define TEXTURESHADER_HPP

#include "../Shader.h"
#include "../../texture/Texture.hpp"
#include "../../../math/matrix/mat4/Matrix4.h"
#include <iostream>
#include "../../../input/key/KeyInput.h"
#include "../../../input/mouse/MouseInput.h"
#include <string>

namespace jpl{

    class TextureShader : protected Shader{


        protected:
            
            /**
             * Change the transformation matrix4.
             * Anyway this method calculates only coordinates on screen and scaling;
             * for rotating you should invoke other methods
             * @param x x coord of screen
             * @param y y coord of screen
             * @param lastX last x coords of screen, means width of quad 
             * @param lastY last y coords of screen, means height of quad
             * @param offsetX
             * @param offsetY
             * @param w
             * @param h
             * @param wT total width of texture
             * @param hT total height of texture
             * @return array of float containing the 4 points of quad of the texture
             */ 
            virtual void calculateTextureCoords(int x, int y, int lastX, int lastY, int offsetX, int offsetY, int w, int h, int wT, int hT);


        public:

            jgl::Matrix4* rotation;

            TextureShader(std::string* vertexFilePath, std::string* fragmentFilePath);
            TextureShader();

            /**
             * Draw whole texture beginning from bottom-left window
             * @param texture
             */ 
            virtual void draw(Texture* texture);

            /**
             * @param texture
             * @param x x coord of window to draw begin from
             * @param y y coord of window to draw begin from
             * @param lastX last x coords of screen
             * @param lastY last y coords of screen
             * @param offsetX offset x of texture
             * @param offsetY offset y of texture
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            void draw(Texture* texuture, int x, int y, int lastX, int lastY, int offsetX, int offsetY, int w, int h);


            /**
             * Draw the whole texture beginning from x,y
             * @param texture
             * @param x x coord of window to draw begin from
             * @param y y coord of window to draw begin from
             * @param flag not used. Just for getting around the definition of two method with same parameters
             */ 
            void draw(Texture* texuture, int x, int y, bool flag);
            /**
             * Draw the whole texture beginning from x,y and zooming it 'till lastX;lastY 
             * 
             * Pass 0;0 as zoom's parameter in order to not allow it
             * @param texture
             * @param x x coord of window to draw begin from
             * @param y y coord of window to draw begin from
             * @param lastX last x coords of screen
             * @param lastY last y coords of screen
             * @param flag not used. Just for getting around the definition of two method with same parameters
             */ 
            void draw(Texture* texuture, int x, int y, int lastX, int lastY, bool flag);


            /**
             * Draw the texture beginning from bottom-left of window
             * @param texture
             * @param offsetX offset x of texture
             * @param offsetY offset y of texture
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            void draw(Texture* texuture, int offsetX, int offsetY, int w, int h);

            /**
             * Draw the texture beginning from bottom-left of window
             * @param texture
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            void draw(Texture* texuture, int w, int h);


            
    };
}

#endif