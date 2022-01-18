#include "JsonFile.h"

jpl::JsonFile::JsonFile(std::string* filePath, std::ios_base::openmode open_mode){
    getLocalFile(filePath, open_mode, &this->file);
    opened = true;
    this->saveLenght();
    this->mainObject = new jpl::JsonObject();
}

jpl::JsonFile::JsonFile(std::fstream* file){
    this->file = file;
    opened = true;
    this->saveLenght();
    this->mainObject = new jpl::JsonObject();
}

void jpl::JsonFile::saveLenght(){

    //Saving the lenght of the file

    this->file->seekg(0, this->file->end);  //Move pointer to the end of the file
    this->lenghtFile = this->file->tellg(); //Save lenght
    this->file->seekg(0, this->file->beg); //Move the pointer to the start of file
}


bool jpl::JsonFile::isOpened(){
    return this->opened;
}

std::fstream* jpl::JsonFile::getFile(){
    return this->file;
}

jpl::JsonObject* jpl::JsonFile::getMainObject(){
    return this->mainObject;
}

long jpl::JsonFile::getFileLenght(){
    return this->lenghtFile;
}

jpl::JsonFile::~JsonFile(){
    // this->mainObject;
    // this->file;
}