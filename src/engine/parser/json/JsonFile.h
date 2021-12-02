/**
 * This is a super class for JsonReader and JsonWriter class
 * Here is get and checked status of the file opened 
 * 
 * @author Gabriele-P03
 */ 

#ifndef JSONFILE_H
#define JSONFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include "../../../files/Files.h"
#include "jsonContent/JsonObject.h"

namespace jpl{

    class JsonFile
    {
        protected:

            JsonObject* mainObject;
            std::fstream* file;
            bool opened = false;

            //Contains the lenght of the file
            long lenghtFile;

            //Called by constructor, it save the lenght of the file in @lenghtFile
            void saveLenght();

        public:

            JsonFile(std::string filePath, std::ios_base::openmode open_mode);
            JsonFile(std::fstream* file);
            ~JsonFile();

            bool isOpened();
            std::fstream* getFile();
            JsonObject* getMainObject();

            //return the lenght of the file 
            long getFileLenght();
    };

}

#endif