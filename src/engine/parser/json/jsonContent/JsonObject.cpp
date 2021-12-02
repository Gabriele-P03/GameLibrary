#include "JsonObject.h"
#include "JsonArray.h"

jpl::JsonObject::JsonObject(std::string* name, std::string &stringToParse){
    this->objName =  name;

    this->objs = new std::vector<jpl::JsonObject*>;
    this->arrays = new std::vector<jpl::JsonArray*>;
    this->maps = new std::vector<jpl::JsonMap*>;

    this->parse(stringToParse);
}

jpl::JsonObject::JsonObject(std::string &stringToParse) : JsonObject(new std::string(""), stringToParse) {
    
}

jpl::JsonObject::JsonObject() : JsonObject(new std::string(""), *new std::string("")){
    
}

jpl::JsonObject::JsonObject(std::string* name, std::vector<JsonObject*>* objs, std::vector<JsonArray*>* arrays, std::vector<JsonMap*>* maps){
    this->objName = name;
    this->objs = objs;
    this->arrays = arrays;
    this->maps = maps;
}

std::vector<jpl::JsonObject*>* jpl::JsonObject::getObjects(){return this->objs;}
jpl::JsonObject* jpl::JsonObject::getObject(int index){return this->objs->at(index);}

std::vector<jpl::JsonArray*>* jpl::JsonObject::getArrays(){return this->arrays;}
jpl::JsonArray* jpl::JsonObject::getArray(int index){return this->arrays->at(index);}

std::vector<jpl::JsonMap*>* jpl::JsonObject::getMaps(){return this->maps;}
jpl::JsonMap* jpl::JsonObject::getMap(int index){return this->maps->at(index);}

std::string* jpl::JsonObject::getName(){return this->objName;}
void jpl::JsonObject::setName(std::string* name){this->objName = name;}

void jpl::JsonObject::filterBuffer(char* buffer){

    if(buffer == nullptr){
        std::cout<<"JSON Buffer null";
        return;
    }
   
    std::string str = std::string(buffer);
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    //str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
    str = str.substr(1, str.length() - 2);

    this->parse(str);
}

void jpl::JsonObject::parse(std::string &buffer){

    //Getting name of the current object
    std::string name;
    while(!buffer.empty()){

        char c = buffer.at(0);

        if(this->isValidChar(c)){
            name += c;
        }else{

            if(c == ':'){

                char tmp = buffer.at(1);
                buffer.erase(0, 1);

                //This object is just started
                if(tmp == '{'){
                    this->objs->push_back(new jpl::JsonObject(new std::string(name), buffer));

                //An array is coming
                }else if(tmp == '['){
                    this->arrays->push_back(new jpl::JsonArray(new std::string(name), buffer));
                
                }

                //A Map is coming
                if(isValidChar(tmp) || tmp == '\"'){

                    if(tmp == '\"'){
                        buffer.erase(0, 1);
                    }
                    
                    /*
                        A map's value can a string or a number, then it checks ',', '\"'.
                        A Map can be the last item in a json file, if the map's value 
                        is a number, the next char will the close curly bracket (no comma)
                    */
                    int indexOfEndValue = fmin(buffer.find("\""), fmin(buffer.find(","), buffer.find("}")));
                    indexOfEndValue = fmax(1, indexOfEndValue);
                    //Retrieve the value of the map
                    std::string value = buffer.substr(0, indexOfEndValue);
                    this->maps->push_back(new jpl::JsonMap(name, value));
                    buffer.erase(0, indexOfEndValue-1);
                }
                name.clear();
            }else if(isCloseCurlyBracket(c)){
                return;
            }
        }

        buffer.erase(0, 1);
    }
}

jpl::JsonObject::~JsonObject(){
    // this->objName;
    // this->objs;
    // this->arrays;
    // this->maps;
}

bool jpl::JsonObject::isValidChar(char c){
    return c != '\n' && c != ',' && c != '\"' && c != '\'' && c != ':' &&
    !this->isOpenCurlyBracket(c) && !this->isCloseCurlyBracket(c) &&
    !this->isOpenSquareBracket(c) && !this->isCloseSquareBracket(c);
}

bool jpl::JsonObject::isOpenCurlyBracket(char c){    return c == '{';}
bool jpl::JsonObject::isCloseCurlyBracket(char c){    return c == '}';}
bool jpl::JsonObject::isOpenSquareBracket(char c){    return c == '[';}
bool jpl::JsonObject::isCloseSquareBracket(char c){ return c == ']';}

std::string jpl::JsonObject::str(){

    std::string buffer;

    if(this->objName->size() > 0){
        buffer = "\"" + *this->objName + "\":";
    }
    buffer += "{";

    for(int i = 0; i < this->objs->size(); i++){
        buffer += this->objs->at(i)->str();

        if(i < this->objs->size() - 1 || this->arrays->size() > 0 || this->maps->size() > 0){
            buffer += ",";
        }

        buffer += "\n";
    }

    for(int i = 0; i < this->arrays->size(); i++){

        buffer += this->arrays->at(i)->str();

        if(i < this->arrays->size() - 1 || this->maps->size() > 0){
            buffer += ",";
        }

        buffer += "\n";
    }

    for(int i = 0; i < this->maps->size(); i++){

        buffer += this->maps->at(i)->str();

        if(i < this->maps->size() - 1){
            buffer += ",";
        }

        buffer += "\n";
    }

    buffer += "\t}";

    return buffer;
}