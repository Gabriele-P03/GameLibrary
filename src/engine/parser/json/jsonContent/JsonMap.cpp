#include "JsonMap.h"

jpl::JsonMap::JsonMap(std::string key, std::string value){

    this->key = new std::string(key);
    this->value = new std::string(value);
}

jpl::JsonMap::JsonMap() : JsonMap("", ""){

}

std::string* jpl::JsonMap::getKey(){ return this->key; }
std::string* jpl::JsonMap::getValue() { return this->value; }
void jpl::JsonMap::setKey(std::string* key) { this->key = key;}
void jpl::JsonMap::setValue(std::string* value) {this->value = value;}

jpl::JsonMap::~JsonMap(){
     this->key;
     this->value;
}

std::string jpl::JsonMap::str(){
    return "\"" + *this->key + "\" : \"" + *this->value + "\"";
}