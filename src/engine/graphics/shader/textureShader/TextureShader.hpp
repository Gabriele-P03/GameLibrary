/**
 * Draw texture in 2D case. 2D is refered to texture, not to rotation. You can rotate it around Y/X axis, too.
 * This shader has own rotation matrix which you can apply your transformations on
 *
 * A lots of drawing methods are available. Check their doc to get more info. 
 * Anyway, even if OpenGl'coords range is [-1;+1] with center [0;0] (window center), you don't need to care about it.
 * Once you invoke a more detailed method (coords where render textute), it will calculate coords in range [-1;+1].
 * WARNING: This shader NOT check if coords are in range of screen width-height
 * 
 * Each transformation (Rotation, Scale and Translation) is stored inside own Matrix4.
 * Scaling and Translation is done by function itselves, you just be care about, if you need it, to rotate via
 * the Matrix4 rotation (the only one public in this class...) 
 * 
 * A single transformation matrix is passed to shader program. It is obtained postmultipling scale to rotation matrix, then translation one
 * 
 * TextureShader's vertex shader core requires a combined matrix in order to render stuff, this due to
 * 2D game's map rendering, but if you're gonna rendering GUI like player's inventory, 
 * then it must not be suboordinated to a camera, you must pass an identity matrix to shader program via:
 * 
 * glUniformMatrix4fv(glGetUniformLocation(*shader->getShaderProgram(), "combined"), 1, GL_FALSE, &(new jgl::Matrix4())->idt()->matrix[0][0];
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
#include "../../../utils/WindowInfo.hpp"
#include <string>


namespace jpl{

    class TextureShader : public Shader{


        protected:
            
            /**
             * Change the transformation matrix4.
             * Anyway this method calculates only coordinates on screen and scaling;
             * for rotating you should invoke other methods
             * @param x x coord of screen
             * @param y y coord of screen
             * @param widthX width of quad 
             * @param heightY height of quad
             * @param offsetX
             * @param offsetY
             * @param w
             * @param h
             * @param wT total width of texture
             * @param hT total height of texture
             * @return array of float containing the 4 points of quad of the texture
             */ 
            virtual void calculateTextureCoords(int x, int y, int widthX, int heightY, int offsetX, int offsetY, int w, int h, int wT, int hT);

            jgl::Matrix4* scale;
            jgl::Matrix4* translation;

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
             * @param widthX width of quad 
             * @param heightY height of quad
             * @param offsetX offset x of texture
             * @param offsetY offset y of texture
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            void draw(Texture* texuture, int x, int y, int widthX, int heightY, int offsetX, int offsetY, int w, int h);


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
             * @param widthX width of quad 
             * @param heightY height of quad
             * @param flag not used. Just for getting around the definition of two method with same parameters
             */ 
            void draw(Texture* texuture, int x, int y, int widthX, int heightY, bool flag);


            /**
             * Draw the texture beginning from bottom-left of window
             * @param texture
             * @param widthX width of quad 
             * @param heightY height of quad
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            void draw(Texture* texuture, int widthX, int heightY, int w, int h);

            /**
             * Draw the texture beginning from bottom-left of window
             * @param texture
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            void draw(Texture* texuture, int w, int h);

            static TextureShader* TEXTURE_SHADER_DEFAULT;

    };  
}


#endif