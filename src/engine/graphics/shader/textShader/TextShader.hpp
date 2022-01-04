/**
 * Abstraction of text rendering shader.
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
 * Blending function in enabled for each text shader you gonna contruct, if you don't need it, just disable it  
 * 
 * @author Gabriele-P03
 */ 

#ifndef TEXTSHADER_HPP
#define TEXTSHADER_HPP

#include <string>
#include "../../../../files/Files.h"
#include "../planeShader/TextureShader.hpp"

namespace jpl{

    class TextShader : protected TextureShader{

        private:

            struct Characters{
                int x, y;
            };

            Characters* chars;

            Texture* font;

            
        public: 
            /**
             * Construct a new text shader with given BitMap font, Vertex and Shader codes
             */ 
            TextShader(std::string* pathToFont, std::string* pathToVertex, std::string* pathToFragment);
            /**
             * Construct a new text shader with default BitMap font and new Vertex and Shader codes
             */ 
            TextShader(std::string* pathToVertex, std::string* pathToFragment);
            /**
             * Construct a new text shader with given BitMap font and default Vertex and Shader codes
             */ 
            TextShader(std::string* pathToFont);
            /**
             * Construct a new text shader with default BitMap font, Vertex and Shader code
             */ 
            TextShader();

            /**
             * Render the given string
             * @param text
             * @param x
             * @param y
             */ 
            void render(std::string* text, int x, int y);

            /**
             * Called for loading font
             * @param rows number of rows in your font
             * @param cols number of cols in your font
             * @param size width and height of a box containing char
             * @param offset padding between each box, which must be the same btween rows and cols
             */ 
            void loadFont(int rows, int cols, int sizeX, int sizeY, int offset);


            static TextShader* TEXT_SHADER_DEFAULT;
    };
}




#endif