/**
 * Json Parser Library for C++
 * Reader and Writer available
 * 
 * This is a Json Parser Library for C++
 * 
 * @author Gabriele-P03
 */ 

#ifndef JSONREADER_H
#define JSONREADER_H

#include "JsonFile.h"
#include <string>

namespace jpl{
    
    class JsonReader : public JsonFile
    {
        private:
            
            //Contains the amount of byte read
            size_t result;

            //Tell if the whole stream has been read
            //If this is false, you should check how many bytes have been read via @result 
            bool readSuccessully;

        public:
            JsonReader(std::string filePath);
            ~JsonReader();

            //Called on JsonReader constructor in order to parse the json file
            void parse(std::string filePath);

            bool hasBeenReadSuccessfully();
            size_t getAmountBytesRead();
    };
    
}

#endif