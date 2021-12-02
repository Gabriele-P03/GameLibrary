#include "JsonReader.h"

jpl::JsonReader::JsonReader(std::string filePath) : jpl::JsonFile::JsonFile(filePath, std::ios_base::in){

    this->parse(filePath);
}

void jpl::JsonReader::parse(std::string filePath){

    char* buffer = new char[this->getFileLenght()];
    this->file->read(buffer, this->lenghtFile);

    this->result = this->file->gcount();    //store into result the amount of bytes read

    if(this->file){
        this->readSuccessully = true;
    }else{
        this->readSuccessully = false;
        std::cout<<"Could not read: "<<filePath<<". Error: "<<errno;
    }

    this->mainObject->filterBuffer(buffer);
}

size_t jpl::JsonReader::getAmountBytesRead(){
    return this->result;
}

bool jpl::JsonReader::hasBeenReadSuccessfully(){
    return this->readSuccessully;
}

jpl::JsonReader::~JsonReader(){
}