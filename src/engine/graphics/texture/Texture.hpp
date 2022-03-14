/**
 * This is an abstraction for texture.
 * PNG files are stored inside an unsigned char vector as RGBA.
 * Once loaded, if no errors occurred, it will also generate a new OpenGl's texture which
 * ID will be stored inside the static unsigned int vector declared below 
 * 
 * PNG file is loaded via lodepng library
 * @link https://github.com/lvandeve/lodepng
 * @author Ivandeve 
 * 
 *  @author Gabriele-P03 
 */ 

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include "../../../files/Files.h"
#include "lodepng.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

namespace jpl{

    class Texture{

        private:
        
            static std::vector<unsigned int*> textureIDs;

            typedef struct{

                unsigned int* textureID;
                unsigned int h;
                unsigned int w;
                std::vector<unsigned char> data;

            }image ;
            image* img;

            //Generate a new OpenGl's buffer for texture and save the ID inside the vector
            void genTexture();

        public:

            //Load the image at the given path
            Texture(std::string path);

            unsigned int getHeight();
            std::vector<unsigned char>* getData();
            unsigned int getWidth();
            unsigned int* getTextureID();

            //Draw this texture
            void draw();
    };
}

#endif