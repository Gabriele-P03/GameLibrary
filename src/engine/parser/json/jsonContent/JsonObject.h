#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <vector>
#include <string>
#include <algorithm>
#include "JsonMap.h"

#include <iostream>
#include <cmath>

namespace jpl{
    
    class JsonArray;

    class JsonObject
    {
        private:
            std::string* objName;

            std::vector<JsonObject*>* objs;
            std::vector<JsonArray*>* arrays;
            std::vector<JsonMap*>* maps;

        public:

            /**
             * @param name name of the current object
             * @param stringToParse the whole object that will be parsed
             */ 
            JsonObject(std::string* name, std::string &stringToParse);

            /**
             * Objects in Array has no name, you should use this constructor in this case
             * @param stringToParse the whole object that will be parsed
             */ 
            JsonObject(std::string &stringToParse);

            /**
             * @param objs pointer to vector of JsonObjects
             * @param arrays pointer to vector of JsonObjects
             * @param maps pointer to vector of JsonObjects
             */ 
            JsonObject(std::string* name, std::vector<JsonObject*>* objs, std::vector<JsonArray*>* arrays, std::vector<JsonMap*>* maps);
            JsonObject();

            ~JsonObject();


            //Return the vector containing all Json Objects of the current object
            std::vector<JsonObject*>* getObjects();
            /**
                Return the object at the given index
                @param index will NOT be checked
            */
            JsonObject* getObject(int index);


            //Return the vector containing all Json Arrays of the current object
            std::vector<JsonArray*>* getArrays();
            /**
                Return the array at the given index
                @param index will NOT be checked
            */
            JsonArray* getArray(int index);


            //Return the vector containing all Json Maps of the current object
            std::vector<JsonMap*>* getMaps();
            /**
                Return the map at the given index
                @param index will NOT be checked
            */
            JsonMap* getMap(int index);
            
            //Return the name of the current object
            std::string* getName();

            //Set the name of this object
            void setName(std::string* name);

            //Filter the given buffer, removing '\n', '\"', ' ' and first and last curly brackets
            void filterBuffer(char* buffer);

            //Parse the given buffer
            void parse(std::string &buffer);

            //Return if the given char is a valid one (not brackets, comma ecc...)
            bool isValidChar(char c);

            //Return if the given char is an opening curly bracket
            bool isOpenCurlyBracket(char c);

            //Return if the given char is a closing curly bracket
            bool isCloseCurlyBracket(char c);

            //Return if the given char is an opening square bracket
            bool isOpenSquareBracket(char c);

            //Return if the given char is an closing square bracket
            bool isCloseSquareBracket(char c);

            //return this array as string
            std::string str();

   };

}

#endif