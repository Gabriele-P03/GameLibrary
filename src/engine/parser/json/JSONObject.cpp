#include "JSONObject.hpp"

JSON::JSONObject::JSONObject(std::string jsonAsString) :
JSON::JSONObject::JSONObject(jsonAsString, 0){}

JSON::JSONObject::JSONObject(std::string jsonAsString, unsigned int offset){

    std::string buffer = "";

    unsigned int i;

    for(i = offset; i < jsonAsString.size(); i++){

        char current = jsonAsString.at(i);

        if(current == '{'){
            JSON::JSONObject obj = JSON::JSONObject(jsonAsString, i+1);
            obj.name = buffer;
            this->objects.push_back(obj);
            i += obj.size;
        }else if(current == '['){
            JSON::JSONArray array = JSON::JSONArray(jsonAsString, i+1);
            array.name = buffer;
            this->arrays.push_back(array);
            i += array.getSize();
        }else if(current == ','){
            if(!buffer.empty())
                this->maps.push_back(JSON::JSONMap(buffer));
            else
                continue;
        }else if(current == '}'){
            i++;
            break;  
        }else{
            buffer += current;
            continue;
        }

        buffer = "";
    }

    if(!buffer.empty()){
        this->maps.push_back(JSON::JSONMap(buffer));
    }
    
    this->size = i - offset;
}

unsigned int JSON::JSONObject::getSize(){
    return this->size;
}

std::string* JSON::JSONObject::to_string(){

    std::string buffer;

    if(!this->name.empty()){
        buffer += "\"" + this->name + "\":";
    }

    buffer += "{";

    for(int i = 0; i < this->objects.size(); i++){
        buffer += *this->objects.at(i).to_string();
        if(i < this->objects.size()-1 || this->arrays.size() > 0 || this->maps.size() > 0){
            buffer += ",";
        }
    }
    for(int i = 0; i < this->arrays.size(); i++){
        buffer += *this->arrays.at(i).to_string();
        if(i < this->arrays.size()-1 || this->maps.size() > 0){
            buffer += ",";
        }
    }
    for(int i = 0; i < this->maps.size(); i++){
        buffer += *this->maps.at(i).to_string();
        if(i < this->maps.size()-1){
            buffer += ",";
        }
    }

    buffer += "}";

    return new std::string(buffer);
}