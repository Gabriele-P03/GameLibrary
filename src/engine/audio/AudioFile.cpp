#include "AudioFile.h"

jpl::AudioFile::AudioFile(std::string pathToFile){
    this->file = new std::fstream();
    getInternalFile(pathToFile, std::ios_base::in, &file);
    this->read(file);
}

jpl::AudioFile::AudioFile(std::fstream* file){
    this->read(file);
}

void jpl::AudioFile::read(std::fstream* file){
   
    int _headerSize = sizeof(this->wav_h);
    file->read((char*)&this->wav_h.RIFF[0], _headerSize);
    this->dataBytesLength = sizeof(unsigned char) * this->wav_h.Subchunk2Size;
    this->data = new char[this->dataBytesLength];
    file->read(data, this->dataBytesLength);
}

jpl::AudioFile::wav_head* jpl::AudioFile::getHeader(){
    return &this->wav_h;
}

char* jpl::AudioFile::getData(){
    return this->data;
}

int jpl::AudioFile::getDataLength(){
    return this->dataBytesLength;
}

jpl::AudioFile::~AudioFile(){
    this->file->close();
    delete &this->wav_h;
}