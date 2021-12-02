#include "Audio.h"


jpl::Audio::Audio(jpl::AudioFile* audioFile){

    this->audioFile = audioFile;
    int err;

    //To clear error buffer
    alGetError();

    //Generating new integers inside buffers. They will be changed by functions
    indexBuffersAudio.push_back(0);
    indexSourcesAudio.push_back(0);

    //Generating buffer
    alGenBuffers(1, &indexBuffersAudio[indexBuffersAudio.size()-1]);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"Error during generating buffer audio: "<<err<<" - "<<getErrorString(err)<<"\n\n";
        exit(-1);
    }
    //Store the address of this buffer index
    this->indexBuffer = &indexBuffersAudio[indexBuffersAudio.size()-1];

    //Passing data to buffer
    alBufferData(
                indexBuffersAudio[indexBuffersAudio.size()-1],
                AL_FORMAT_STEREO16,
                this->audioFile->getData(),
                this->audioFile->getDataLength(),
                this->audioFile->getHeader()->BytesRate/this->audioFile->getHeader()->BlockAlign);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"OpenAl error: generating buffer "<<err;
        exit(-1);
    }



    alGenSources(1, &indexSourcesAudio[indexSourcesAudio.size()-1]);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"OpenAl error: generating source "<<err;
        exit(-1);
    }
    //Store the address of this source index
    this->indexSource = &indexSourcesAudio[indexSourcesAudio.size()-1];

    alSourcei(*this->indexSource, AL_BUFFER, *this->indexBuffer);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"OpenAl error: attaching buffer "<<err;
        exit(-1);
    }

    std::cout<<"New audio created\n";
}

void jpl::Audio::play(){
    int err;
    alSourcePlay(*this->indexSource);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"Could not play audio at buffer source: "<<this->indexSource<<". Error: "<<err<<"\n\n";
    }    

    /*
        THE CODE BELOW HAVE BEEN USED ONLY FOR DEBUG PURPOSE
        

    int flag;
    do{
        alGetSourcei(*this->indexSource, AL_SOURCE_STATE, &flag);
    }while(flag == AL_PLAYING);
    */
}

void jpl::Audio::stop(){
    int err;
    alSourceStop(*this->indexSource);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"Could not stop audio at buffer source: "<<this->indexSource<<". Error: "<<err<<"\n\n";
    }  
}

void jpl::Audio::rewind(){
    int err;
    alSourceRewind(*this->indexSource);
    if( (err = alGetError()) != AL_NO_ERROR){
        std::cout<<"Could not reqind audio at buffer source: "<<this->indexSource<<". Error: "<<err<<"\n\n";
    }
}

void initAudio(){
    
    std::cout<<"Initializing OpenAl...";

    //Passing nullptr, it's gonna select the default device 
    defaultDev = alcOpenDevice(nullptr);

    if(!defaultDev){
        std::cout<<"Could not initialize OpenAl. Error: "<<alcGetError(defaultDev)<<"\n\n";
        exit(-1);
    }

    context = alcCreateContext(defaultDev, NULL);
    alcMakeContextCurrent(context);
    std::cout<<"Done\n\n";
}

void termAudio(){

    std::cout<<"Closing OpenAl...";
    alGetError();

    std::cout<<"Stopping sounds...";
    alSourceStopv(indexSourcesAudio.size(), &indexSourcesAudio[0]);
    int err = alGetError();
    if(err != AL_NO_ERROR){
        std::cout<<"Error during closing sources: "<<err<<"I am not force closing game...";
    }

    std::cout<<"Destroing sources...";
    alDeleteSources(indexSourcesAudio.size(), &indexSourcesAudio[0]);
    err = alGetError();
    if(err != AL_NO_ERROR){
        std::cout<<"Error during destroing sources: "<<err<<"I am not force closing game...";
    }

    std::cout<<"Destroing buffers...";
    alDeleteBuffers(indexBuffersAudio.size(), &indexBuffersAudio[0]);
    err = alGetError();
    if(err != AL_NO_ERROR){
        std::cout<<"Error during destroing buffers: "<<err<<". I am not force closing game...";
    }

    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(defaultDev);
    std::cout<<"Done\n\n";
}

std::string getErrorString(int err){
    
    switch (err) {
        case AL_NO_ERROR: return "AL_NO_ERROR";
        case AL_INVALID_NAME: return "AL_INVALID_NAME";
        case AL_INVALID_ENUM: return "AL_INVALID_ENUM";
        case AL_INVALID_VALUE: return "AL_INVALID_VALUE";
        case AL_INVALID_OPERATION: return "AL_INVALID_OPERATION";
        case AL_OUT_OF_MEMORY: return "AL_OUT_OF_MEMORY";

    default:
        return "Unknown error code";
    }
}