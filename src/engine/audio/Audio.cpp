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
        jpl::Logger::INSTANCE->print("Error during generating buffer audio: " + std::to_string(err) + " - " + getErrorString(err));
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
        jpl::Logger::INSTANCE->print("OpenAl error: generating buffer " + std::to_string(err));
        exit(-1);
    }



    alGenSources(1, &indexSourcesAudio[indexSourcesAudio.size()-1]);
    if( (err = alGetError()) != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("OpenAl error: generating source " + err);
        exit(-1);
    }
    //Store the address of this source index
    this->indexSource = &indexSourcesAudio[indexSourcesAudio.size()-1];

    alSourcei(*this->indexSource, AL_BUFFER, *this->indexBuffer);
    if( (err = alGetError()) != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("OpenAl error: attaching buffer " + err);
        exit(-1);
    }

    jpl::Logger::INSTANCE->print("New audio created");
}

void jpl::Audio::play(){
    int err;
    alSourcePlay(*this->indexSource);
    if( (err = alGetError()) != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("Could not play audio at buffer source: " + std::to_string(*this->indexSource) + ". Error: " + std::to_string(err));
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
        jpl::Logger::INSTANCE->print("Could not stop audio at buffer source: " + std::to_string(*this->indexSource) + ". Error: " + std::to_string(err));
    }  
}

void jpl::Audio::rewind(){
    int err;
    alSourceRewind(*this->indexSource);
    if( (err = alGetError()) != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("Could not reqind audio at buffer source: " + std::to_string(*this->indexSource) + ". Error: " + std::to_string(err));
    }
}

void initAudio(){
    
    jpl::Logger::INSTANCE->print("Initializing OpenAl...");

    //Passing nullptr, it's gonna select the default device 
    defaultDev = alcOpenDevice(nullptr);

    if(!defaultDev){
        jpl::Logger::INSTANCE->print("Could not initialize OpenAl. Error: " + alcGetError(defaultDev));
        exit(-1);
    }

    context = alcCreateContext(defaultDev, NULL);
    alcMakeContextCurrent(context);
}

void termAudio(){

    jpl::Logger::INSTANCE->print("Closing OpenAl...");
    alGetError();

    jpl::Logger::INSTANCE->print("Stopping sounds...");
    alSourceStopv(indexSourcesAudio.size(), &indexSourcesAudio[0]);
    int err = alGetError();
    if(err != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("Error during closing sound sources: " + err);
    }

    jpl::Logger::INSTANCE->print("Destroing sound sources...");
    alDeleteSources(indexSourcesAudio.size(), &indexSourcesAudio[0]);
    err = alGetError();
    if(err != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("Error during destroing sound sources: " + err);
    }

    jpl::Logger::INSTANCE->print("Destroing sound buffers...");
    alDeleteBuffers(indexBuffersAudio.size(), &indexBuffersAudio[0]);
    err = alGetError();
    if(err != AL_NO_ERROR){
        jpl::Logger::INSTANCE->print("Error during destroing sound buffers: " + err);
    }

    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(defaultDev);
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