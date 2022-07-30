/**
 * Abstraction of text rendering shader.
 * 
 * Since you could need to render text in a 3D world (e.g. player name above the model), you can pass
 * the combined matrix of the persp camera, otherwise just pass an idt matrix
 * 
 * You could construct your own object of this class using your font. Anyway, there's alredy one
 * static instance with the default font of this library
 * 
 * A font for this library is a PNG file wich is composed by row and cols. 
 * 
 * If you instance your own, you must call loadFont(int, int, int, int) before render any text; this will load 
 * in a Characters* all chars drawn, saving their top-left starting coordinates.
 * The first int is the amount of rows.
 * The second one is the amound of cols.
 * The third one is the size of each box in pixel.
 * THe fourth one is the padding between row-row and col-col
 * 
 * On render() call, the given string parameter (text to be rendered) will be checked char by char.
 * The single char will be pointed to the struct and then it takes coords of font.
 * 
 * This shader can be used for rendering text either in 2D game or 3D one.
 * Before call render() method, send the comboned matrix of the camera to the shader
 * via TextShader#setCombinedMatrix() or pass an identity matrix if you wanna render as 2D
 * 
 * @author Gabriele-P03
 */ 

#ifndef TEXTSHADER_HPP
#define TEXTSHADER_HPP

#include <string>
#include "../../../files/Files.h"
#include "TextureShader.hpp"

namespace jpl{

    class TextShader : public TextureShader{

        private:
        
            int size, offset;

            struct Characters{
                int x, y;
            };

            Characters* chars;

            Texture* font;

            
        public: 
            /**
             * Construct a new text shader with given BitMap font, Vertex and Shader codes
             */ 
            TextShader(std::string pathToFont, std::string pathToVertex, std::string pathToFragment);
            /**
             * Construct a new text shader with default BitMap font and new Vertex and Shader codes
             */ 
            TextShader(std::string pathToVertex, std::string pathToFragment);
            /**
             * Construct a new text shader with given BitMap font and default Vertex and Shader codes
             */ 
            TextShader(std::string pathToFont);
            /**
             * Construct a new text shader with default BitMap font, Vertex and Shader code
             */ 
            TextShader();

            /**
             * Render the given string with the given mix of colors
             * @param text
             * @param x
             * @param y
             * @param z
             * @param w
             * @param h
             * @param red
             * @param green
             * @param blue
             * @param alpha
             */ 
            void render(std::string text, float x, float y, float z, float w, float h, float red, float green, float blue, float alpha);
            


            /**
             * Render the given string
             * @param text
             * @param x
             * @param y
             * @param z
             * @param w
             * @param h
             * @param colors
             */ 
            void render(std::string text, float x, float y, float z, float w, float h, float* colors);


            /**
             * Render the given string
             * @param text
             * @param x
             * @param y
             * @param z
             * @param w
             * @param h
             */ 
            void render(std::string text, float x, float y, float z, float w, float h);

            /**
             * Called for loading font
             * @param rows number of rows in your font
             * @param cols number of cols in your font
             * @param size width and height of a box containing char
             * @param offset padding between each box, which must be the same btween rows and cols
             */ 
            void loadFont(int rows, int cols, int size, int offset);


            /**
             * Since you could need to draw text either on 2D screen (text button on GameMenu)
             * or in a 3D space (players' name at the top of the model), you will need to
             * set a ceratin combined matrix:
             *  Identity in the first case, otherwise combined matrix of the camera
             * 
             * @param combinedMatrix
             */ 
            virtual void setCombinedMatrix(glm::mat4 combinedMatrix);


            /**
             * @return the size of font's chars
             */
            int getFontSize();

            static TextShader* TEXT_SHADER_DEFAULT;
    };
}

#endif