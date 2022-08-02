#include "Logger.hpp"

jpl::Logger* jpl::Logger::INSTANCE = new jpl::Logger();

jpl::Logger::Logger(){

    this->file = new std::fstream();
    this->file->open(*getLocalFile("logs/" + this->getFileNameOfInstance() + ".txt"), std::ios_base::out);

    if(!file){
        std::cout<<"Could not create log file";
        exit(EXIT_FAILURE);
    }
}

std::string jpl::Logger::getFileNameOfInstance(){

    std::tm *ltm = this->getTM();

    return  std::to_string((*ltm).tm_mday) + "-" + 
            std::to_string((*ltm).tm_mon+1) + "-" + 
            std::to_string((*ltm).tm_year + 1900) + "_" +
            std::to_string((*ltm).tm_hour) + "-" +
            std::to_string((*ltm).tm_min) + "-" +
            std::to_string((*ltm).tm_sec);
}

void jpl::Logger::print(std::string msg){

    msg = "[" + this->getFileNameOfInstance() + "]: " + msg + "\n";
    this->file->write(msg.c_str(), msg.size());
    this->file->flush();

    std::cout<<msg;
}

void jpl::Logger::closeLogger(){

    this->print("Logger closed");
    this->file->close();
}
