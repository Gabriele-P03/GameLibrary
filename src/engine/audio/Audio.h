/**
 * This is just an implementation of OpenAl library
 * 
 * The library must be initialized via initAudio() which is already called by 
 * Main#initialize(). OpenAl is initialized once a device is opened.
 * 
 * Every audio has own buffer for data and own source. These two values are stored in
 * indexBuffersAudio and indexSourcesAudio, which are both vectors of uint
 * 
 * Once game is gonna be closed, Main#terminate() will call termAudio() which
 * destroy buffers and sources, the current context and close the device
 * 
 * @author Gabriele-P03
 */ 

#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include "AudioFile.h"
#include <vector>

static ALCdevice* defaultDev;
static ALCcontext* context;


static std::vector<unsigned int> indexBuffersAudio;
static std::vector<unsigned int> indexSourcesAudio; 

/**
 * Initialize OpenAl opening the default device via 
 */ 
void initAudio();

/**
 * Close Audio Library
 */ 
void termAudio();

/**
 * Be careful to pass an AL_ERROR, not an ALC_ERROR
 * @param err error index
 * @return the error as string
 */ 
std::string getErrorString(int err);

namespace jpl{

    class Audio{

        private:
            jpl::AudioFile* audioFile;

            //These are the pointer to the buffer's index and source's index 
            unsigned int* indexBuffer;
            unsigned int* indexSource; 

        public:

            Audio(jpl::AudioFile* audioFile);

            void play();

            void rewind();

            void stop();
    };

}

#endif