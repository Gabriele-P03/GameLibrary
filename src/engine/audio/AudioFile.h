/**
 * I have decided to not use alut parser, so I have written this one
 * This is a WAV only file parser - other format could be added later.
 * 
 * An instance of this class contains header data inside struct wav_head;
 * once header and data have been read, this object is passed to Audio.cpp
 * 
 * @author Gabriele-P03
 */ 

#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <fstream>
#include <iostream>
#include "../../files/Files.h"

namespace jpl{

    class AudioFile{
        private:

            typedef struct{

                //  RIFF Chunk Descriptor
                uint8_t RIFF[4];                //RIFF Header
                uint32_t ChunkSize;             //RIFF ChunkSize
                uint8_t WAVE[4];                //WAVE Header

                // "fmt" subchunk 
                uint8_t fmt[4];                 //Fmt Header
                uint32_t Subchunk1Size;         //Size of the fmt chunk
                uint16_t AudioFormat;           //AudioFormat 1=PCM 6=mulaw
                uint16_t NumChannels;           //Number of channels 1=Mono 2=Stereo
                uint32_t SampleRate;            //Sample for Sec
                uint32_t BytesRate;             //Bytes per Sec
                uint16_t BlockAlign;            //2=16bit Mono 4=16bit Stereo
                uint16_t BitsPerSample;         //Bits per sample

                // Data subchunk
                uint8_t Subchunk2ID[4];
                uint32_t Subchunk2Size;
                
            }wav_head;

            wav_head wav_h;

            //Store the lenth of data raw
            int dataBytesLength;
            //This is the buffer which will contains all raw data of the wav file
            char* data;
            
        public:

            std::fstream* file;
            
            AudioFile(std::string* pathToFile);
            AudioFile(std::fstream* file);

            //Read the header and then the data raw
            void read(std::fstream* file);

            wav_head* getHeader();
            char* getData();
            int getDataLength();

            ~AudioFile();
    };
}

#endif