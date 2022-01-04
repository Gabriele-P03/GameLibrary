#ifndef JSONWRITER_H
#define JSONWRITER_H

#include "JsonFile.h"
#include "jsonContent/JsonArray.h"
#include "jsonContent/JsonMap.h"

namespace jpl{

    class JsonWriter : JsonFile
    {
        private:

        public:


            JsonWriter(std::fstream* file, jpl::JsonObject* obj);
            JsonWriter(std::string* path, jpl::JsonObject* obj);
            JsonWriter(std::fstream* file);
            JsonWriter(std::string* path);
            JsonWriter();

            void write();

            void close();

    }; 

}

#endif