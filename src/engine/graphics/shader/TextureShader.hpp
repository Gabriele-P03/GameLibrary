/**
 * If you wanna draw a texture depending by the camera, call TextureShader#setCombinedMatrix() passing camera's one,
 * otherwise pass an identity matrix 
 * 
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
 * 2D gameplay rendering, but if you're gonna rendering GUI like player's inventory, 
 * then it must not be suboordinated to a camera, you must pass an identity matrix to shader program via:
 * 
 * glUniformMatrix4fv(glGetUniformLocation(*shader->getShaderProgram(), "combined"), 1, GL_FALSE, &(new jgl::Matrix4())->idt()->matrix[0][0];
 * 
 * @author Gabriele-P03
 */ 

#ifndef TEXTURESHADER_HPP
#define TEXTURESHADER_HPP

#include "Shader.hpp"
#include "../texture/Texture.hpp"
#include <iostream>
#include "../../input/key/KeyInput.h"
#include "../../input/mouse/MouseInput.h"
#include "../../utils/WindowInfo.hpp"
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
             * @param z z coord of screen
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
            inline virtual void calculateTextureCoords(float x, float y, float z, int widthX, int heightY, 
                
                int offsetX, int offsetY, int w, int h, int wT, int hT)
                
                {

                    int widthWindow = jpl::WindowSize::INSTANCE.w, heightWindow = jpl::WindowSize::INSTANCE.h;

                    if(widthX < widthWindow){
                        x *= (float)widthWindow/(float)jpl::MAX_WINDOW_W;
                        widthX *= (float)widthWindow/(float)jpl::MAX_WINDOW_W;
                    }
                    if(heightY < heightWindow){
                        y *= (float)heightWindow/(float)jpl::MAX_WINDOW_H;
                        heightY *= (float)heightWindow/(float)jpl::MAX_WINDOW_H;
                    }

                    //UVs are store in an array different by the one of shader's coordinates
                    this->vertices[18] = (float)offsetX/(float)wT;
                    this->vertices[19] = (float)offsetY/(float)hT;

                    this->vertices[3] = (float)offsetX/(float)wT;
                    this->vertices[4] = this->vertices[19] + (float)h/(float)hT;

                    this->vertices[8] = this->vertices[18] + (float)w/(float)wT; 
                    this->vertices[9] = this->vertices[19] + (float)h/(float)hT;

                    this->vertices[13] = this->vertices[18] + (float)w/(float)wT;
                    this->vertices[14] = (float)offsetY/(float)hT;

                    float widthRatio = (float)widthX/(float)widthWindow;
                    float heightRatio = (float)heightY/(float)heightWindow;

                    float newX = -1.0f + 2.0f * ( (float)(x+widthX/2.0f)/(float)widthWindow ),
                        newY = -1.0f + 2.0f * ( (float)(y+heightY/2.0f)/(float)heightWindow );

                    /*
                        As already known OpenGl works in range [-1; +1]. Now, considering that most of monitors is not
                        a quad, we need to scale down x and y as the texture supplies.
                        Do not care if your texture width is greater than window's; It will do it
                    */
                    this->scale = glm::vec3(
                                (wT < widthWindow ?  widthRatio : 1/widthRatio), 
                                (hT < heightWindow ? heightRatio : 1/heightRatio),
                                1.0f);

                    this->translation = glm::vec3(newX, newY, z);
            }


        public:

            TextureShader(std::string vertexFilePath, std::string fragmentFilePath);
            TextureShader();

            /**
             * Draw whole texture beginning from bottom-left window
             * @param texture
             */ 
            inline virtual void draw(Texture* texture){
                this->draw(texture, 0, 0, 0, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight());
            }

            /**
             * @param texture
             * @param x x coord of window to draw begin from
             * @param y y coord of window to draw begin from
             * @param z z coord of window to draw begin from
             * @param widthX width of quad 
             * @param heightY height of quad
             * @param offsetX offset x of texture
             * @param offsetY offset y of texture
             * @param w width of texture to draw
             * @param h height of texture to draw
             */ 
            inline void draw(Texture* texture, float x, float y, float z, int widthX, int heightY, int offsetX, int offsetY, int w, int h){

                this->calculateTextureCoords(x, y, z, widthX, heightY, offsetX, offsetY, w, h, texture->getWidth(), texture->getHeight());

                this->useProgram();

                this->bind();
                glBindVertexArray(*this->VAO);
            
                this->pushMatrixTransformation();
                texture->draw();
                glDrawElements(GL_TRIANGLES, this->_sizeIndices, GL_UNSIGNED_INT, (void*)0);
            }

            /**
             * Draw the whole texture beginning from x,y
             * @param texture
             * @param x x coord of window to draw begin from
             * @param y y coord of window to draw begin from
             * @param z z coord of window to draw begin from
             * @param flag not used. Just for getting around the definition of two method with same parameters
             */ 
            inline void draw(Texture* texture, float x, float y, float z){
                this->draw(texture, x, y, z, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight());
            }
            
            
            /**
             * Draw the whole texture beginning from x,y and zooming it 'till lastX;lastY 
             * 
             * Pass 0;0 as zoom's parameter in order to not allow it
             * @param texture
             * @param x x coord of window to draw begin from
             * @param y y coord of window to draw begin from
             * @param z z coord of window to draw begin from
             * @param widthX width of quad 
             * @param heightY height of quad
             * @param flag not used. Just for getting around the definition of two method with same parameters
             */ 
            inline void draw(Texture* texture, float x, float y, float z, int widthX, int heightY){
                this->draw(texture, x, y, z, widthX, heightY, 0.0f, 0.0f, texture->getWidth(), texture->getHeight());
            }



            /**
             * Since VBO now has 5 value (3 vertices and 2 Texure Vertices), we need to override it
             */ 
            inline virtual void vertexAttrib() override{
                    //Enabling coords on screen
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                //Enabling texture coords
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);
            }


            static TextureShader* TEXTURE_SHADER_DEFAULT;

    };  
}


#endif