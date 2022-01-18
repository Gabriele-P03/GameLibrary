#include "JsonWriter.h"

jpl::JsonWriter::JsonWriter(std::string* filePath, jpl::JsonObject* obj) : jpl::JsonFile(filePath, std::ios_base::out){
    this->mainObject = obj;
}

jpl::JsonWriter::JsonWriter(std::fstream* file, jpl::JsonObject* obj) : jpl::JsonFile(file){
    this->mainObject = obj;
}

jpl::JsonWriter::JsonWriter(std::string* filePath) : jpl::JsonFile(filePath, std::ios_base::out){}
jpl::JsonWriter::JsonWriter(std::fstream* file) : jpl::JsonFile(file){}

void jpl::JsonWriter::write(){

    if(this->mainObject != nullptr){
        this->file->write("{\n", 2);

        std::string buffer;

        for(int i = 0; i < this->mainObject->getObjects()->size(); i++){
            buffer += "\t" + this->mainObject->getObjects()->at(i)->str();

            if(i < this->mainObject->getObjects()->size()-1 || this->mainObject->getArrays()->size() > 0){
                buffer += ",\n\n";
            }
        }

        for(int i = 0; i < this->mainObject->getArrays()->size(); i++){
            buffer += "\t" + this->mainObject->getArrays()->at(i)->str();

            if(i < this->mainObject->getArrays()->size()-1 || this->mainObject->getMaps()->size() > 0){
                buffer += ",\n\n";
            }
        }

        for(int i = 0; i < this->mainObject->getMaps()->size(); i++){
            buffer += "\t" + this->mainObject->getMaps()->at(i)->str();
        }

        this->file->write(buffer.c_str(), buffer.size());
        this->file->write("\n", 1);
        this->file->write("}", 1);
    }
}

void jpl::JsonWriter::close(){
    this->file->close();
}   