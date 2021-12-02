#include "PNGDecoder.hpp"

jpl::PNGDecoder::PNGDecoder(std::string* pathToFile){

    std::fstream* file = new std::fstream; 
    getInternalFile(pathToFile->c_str(), std::ios_base::in, &file);

    file->seekg(0, file->end);
    unsigned int size = file->tellg();
    file->seekg(0, file->beg);

    char* buffer = new char[size];
    file->read(buffer, 8);

    file->read(&buffer[8], size-8);

    std::cout;
}