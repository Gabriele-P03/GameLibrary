#include "JsonArray.h"
#include "JsonObject.h"

jpl::JsonArray::JsonArray(std::string* name, std::string &stringToParse){
    this->arrayName =  name;

    this->objs = new std::vector<jpl::JsonObject*>;
    this->arrays = new std::vector<jpl::JsonArray*>;
    this->values = new std::vector<std::string*>;

    this->parse(stringToParse);
}

jpl::JsonArray::JsonArray(std::string &stringToParse) : JsonArray(new std::string(""), stringToParse) {
    
}

jpl::JsonArray::JsonArray() : JsonArray(new std::string(""), *new std::string("")){
    
}

jpl::JsonArray::JsonArray(std::string* name, std::vector<JsonObject*>* objs, std::vector<JsonArray*>* arrays, std::vector<std::string*>* values){
    this->arrayName = name;
    this->objs = objs;
    this->arrays = arrays;
    this->values = values;
}

std::vector<jpl::JsonObject*>* jpl::JsonArray::getObjects(){return this->objs;}
jpl::JsonObject* jpl::JsonArray::getObject(int index){return this->objs->at(index);}

std::vector<jpl::JsonArray*>* jpl::JsonArray::getArrays(){return this->arrays;}
jpl::JsonArray* jpl::JsonArray::getArray(int index){return this->arrays->at(index);}

std::vector<std::string*>* jpl::JsonArray::getValues(){return this->values;}
std::string* jpl::JsonArray::getValue(int index){return this->values->at(index);}

std::string* jpl::JsonArray::getName(){return this->arrayName;}
void jpl::JsonArray::setName(std::string* name){this->arrayName = name;}

void jpl::JsonArray::parse(std::string &buffer){
    buffer.erase(0, 1);
    //Getting name of the current object
    std::string name;
    while(!buffer.empty()){

        char c = buffer.at(0);

        if(this->isValidChar(c)){
            name += c;
        }else{
            
            if(isOpenCurlyBracket(c)){
                this->objs->push_back(new jpl::JsonObject(new std::string(name), buffer));
            }else if(isOpenSquareBracket(c)){
                this->arrays->push_back(new jpl::JsonArray(new std::string(name), buffer));
            }else{
                if(name != ""){
                    this->values->push_back(new std::string(name));
                }
            }

            if(isCloseSquareBracket(c)){
                return;
            }

            name.clear();
        }

        buffer.erase(0, 1);
    }
}

bool jpl::JsonArray::isValidChar(char c){
    return c != '\n' && c != ',' && c != '\"' && c != '\'' && c != ':' &&
    !this->isOpenCurlyBracket(c) && !this->isCloseCurlyBracket(c) &&
    !this->isOpenSquareBracket(c) && !this->isCloseSquareBracket(c);
}

bool jpl::JsonArray::isOpenCurlyBracket(char c){return c == '{';}
bool jpl::JsonArray::isCloseCurlyBracket(char c){return c == '}';}
bool jpl::JsonArray::isOpenSquareBracket(char c){return c == '[';}
bool jpl::JsonArray::isCloseSquareBracket(char c){return c == ']';}

std::string jpl::JsonArray::str(){

    std::string buffer;

    if(this->arrayName->size() > 0){
        buffer = "\"" + *this->arrayName + "\":";
    }
    buffer += "[";

    for(int i = 0; i < this->objs->size(); i++){
        buffer += this->objs->at(i)->str();

        if(i < this->objs->size() - 1 || this->arrays->size() > 0 || this->values->size() > 0){
            buffer += ",";
        }

        buffer += "\n";
    }

    for(int i = 0; i < this->arrays->size(); i++){

        buffer += this->arrays->at(i)->str();

        if(i < this->arrays->size() - 1 || this->values->size() > 0){
            buffer += ",";
        }

        buffer += "\n";
    }

    for(int i = 0; i < this->values->size(); i++){

        buffer += "\"" + *this->values->at(i) + "\"";

        if(i < this->values->size() - 1){
            buffer += ",";
        }else{
            buffer += "\n";
        }
    }

    buffer += "\t]";

    return buffer;
}