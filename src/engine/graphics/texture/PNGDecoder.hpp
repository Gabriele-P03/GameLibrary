/**
 * This is my own PNG parser used to load PNG file texture
 * 
 * 
 * @author Gabriele-P03
 */ 

#ifndef PNGDECODER_H
#define PNGDECODER_H

#include <string>
#include "../../../files/Files.h"

namespace jpl{

    class PNGDecoder
    {

        private:

            typedef struct{
                uint8_t signature[8];
            }data;
            
        public:

            /**
             * Instance a new PNG texture file taken from Internal Folder.
             * Pass the path beginning from resources folder
             */ 
            PNGDecoder(std::string* filePath);

    };
    
}

#endif