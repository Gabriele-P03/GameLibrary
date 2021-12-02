#ifndef JSONARRAY_H
#define JSONARRAY_H

#include <vector>
#include <string>

namespace jpl{

    class JsonObject;

    class JsonArray
    {
        private:
            std::string* arrayName;

            std::vector<JsonObject*>* objs;
            std::vector<JsonArray*>* arrays;
            std::vector<std::string*>* values;

        public:

            /**
             * @param name name of the current object
             * @param stringToParse the whole object that will be parsed
             */ 
            JsonArray(std::string* name, std::string &stringToParse);

            /**
             * Objects in Array has no name, you should use this constructor in this case
             * @param stringToParse the whole object that will be parsed
             */ 
            JsonArray(std::string &stringToParse);

            /**
             * @param objs pointer to vector of JsonObjects
             * @param arrays pointer to vector of JsonObjects
             * @param maps pointer to vector of JsonObjects
             */ 
            JsonArray(std::string* name, std::vector<JsonObject*>* objs, std::vector<JsonArray*>* arrays, std::vector<std::string*>* values);
            JsonArray();

            ~JsonArray();


            //Return the vector containing all Json Objects of the current array
            std::vector<JsonObject*>* getObjects();
            /**
                Return the object at the given index
                @param index will NOT be checked
            */
            JsonObject* getObject(int index);


            //Return the vector containing all Json Arrays of the current array
            std::vector<JsonArray*>* getArrays();
            /**
                Return the array at the given index
                @param index will NOT be checked
            */
            JsonArray* getArray(int index);


            //Return the vector containing all Json Maps of the current array
            std::vector<std::string*>* getValues();
            /**
                Return the map at the given index
                @param index will NOT be checked
            */
            std::string* getValue(int index);
            

            //Return the name of the current object
            std::string* getName();

            //Set the name of this object
            void setName(std::string* name);

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