#include "Files.h"

void getLocalFile(std::string* pathToFile, std::ios_base::openmode __modes, std::fstream** file){

    std::string path = std::string(*getRootPath() + "/" + *pathToFile);

    (**file).open(path, __modes);

    if( !(**file)){
        if(__modes == std::ios_base::in){
            std::cout<<"Could not open file at: "<<path<<". Error: "<<errno;
            exit(EXIT_FAILURE);
        }
    }
}

void getInternalFile(std::string* pathToFile, std::ios_base::openmode _mode, std::fstream** file){
    getLocalFile( new std::string("resources/" + *pathToFile), _mode, file);
}

std::string* getRootPath(){
    
    std::string pathToFile = "";

    //If the os is linux
    #ifdef __linux__
        char path[PATH_MAX];
        ssize_t result = ::readlink("/proc/self/exe", path, sizeof(path)-1);
        if(result != -1){
            path[result] = '\0';
            pathToFile = dirname(path);
        }
            

    #elif _WIN32
        char path[PATH_MAX];

        //When NULL is passed, directory of the exe is returned
        HMODULE hmodule = GetModuleHandle(NULL);
        if(hmodule != NULL){
            GetModuleFileName(hmodule, path, sizeof(path));
        }
        pathToFile = path;
        pathToFile = pathToFile.substr(0, pathToFile.find_last_of('\\'));
    #else

    #endif



    return new std::string(pathToFile);

}

std::string* readFile(std::string* pathToFile){

    std::fstream* file = new std::fstream;
    getInternalFile(pathToFile, std::ios_base::in, &file);
    return readFile(file);
}


std::string* readFile(std::fstream* file){
    if(!file){
        std::cout<<"Could not open file...\n\n";
        return nullptr;
    }else{

        //Store the length of the file in order to create the right sized buffer
        file->seekg(0, file->end);
        unsigned int length = file->tellg();
        file->seekg(0, file->beg);

        char* buffer = new char[length];

        //fstram#read return file without errors once it has been read successfully
        if(file->read(buffer, length)){
            buffer[length] = '\0';
            return new std::string(buffer);
        }else{
            std::cout<<"Error during file reading. I've read only: "<<std::string(buffer);
            return nullptr;
        }
    }
}

std::string* getInternalPath(std::string* path){
    return new std::string(*getRootPath() + "/resources/" + *path);
}

std::string* getLocalFile(std::string* path){
    return new std::string(*getRootPath() + "/" + *path);
}