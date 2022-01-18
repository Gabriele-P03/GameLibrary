/**
 * This is an basic abstraction of a shader program.
 * 
 * It contains only main OpenGl's buffer (VBO and VAO), which can be set via
 * setVertices() and setIndices() passing pointer to buffers and their length
 * 
 * VBO, VAO, fragmentShader, vertexShader, shaderProgram are all stored inside a static vector pointer.
 * Every shader instance has own pointers to relative one inside vector.
 * 
 * e.g.
 *      Assuming that the pointer inside vector is already initialized with a new unsigned int 
 *      via VBOs.push_back(new unsigned int) as you can see in Shader.cpp 
 * 
 *      glGenBuffers(1, VBOs[VBOs.size()-1]);  //Let's instance a new VBO which index's address will be saved inside vector
 *      this->VBO = VBOs[VBOs.size()-1];       //Now let's store in a local variable the address
 * 
 * 
 * I developed this library thinking to make my own cube game, then has already 3 shaders available:
 *  - 3D cube block
 *  - 2D Text Render
 *  - 2D Texture Render
 * 
 * @author Gabriele-P03
 */ 

#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include "../../../files/Files.h"
#include <fstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

typedef unsigned int JPLstartX;
typedef unsigned int JPLstartY;
typedef unsigned int JPLwidthX;
typedef unsigned int JPLheightY;
typedef unsigned int JPLstartXTex;
typedef unsigned int JPLstartYTex;
typedef unsigned int JPLwidthXTex;
typedef unsigned int JPLheightYTex;

/**
 * Called by Main's terminating function, it will destroy all buffers, sources and program shaders
 * which are saved inside the vectors declared above
 */ 
void termShaders();

namespace jpl{

    class Shader
    {
        protected:

            static std::vector<unsigned int*> VBOs;             //Static vector for all VBOs
            static std::vector<unsigned int*> VAOs;             //Static vector for all VAOs
            static std::vector<unsigned int*> EBOs;             //Static vector for all EBOs
            static std::vector<unsigned int*> vertexShaders;    //Static vector for all vertexShaders
            static std::vector<unsigned int*> fragmentShaders;  //Static vector for all fragmentShaders
            static std::vector<unsigned int*> shaderPrograms;   //Static vector for all shaderPrograms

            /*
                They point to the current VBO, VAO, EBO, vertexShaders, fragmentShaders and shaderPrograms
                inside vectors declared above
            */
            unsigned int* VBO;
            unsigned int* VAO;
            unsigned int* EBO;
            unsigned int* vertexShader;
            unsigned int* fragmentShader;
            unsigned int* shaderProgram;

            float* vertices;
            unsigned int _sizeVertices;

            unsigned int* indices;
            unsigned int _sizeIndices;

            //Generates VBO and VAO
            void genMainBuffers();

            //Create shader program by given codes
            void createShader(std::string vertexCode, std::string fragmentCode);

            /**
             *  Bind buffer with the given parameters
            */  
            virtual void bind();

            /*
                Draw the triangles which compose this shader.
                First call glUseProgram() in order to set this shader available for pipeline,
                then call glBindVertexArray(VAO) and then draw elements via glDrawArrays()
            */
            virtual void draw();

            /**
             * Set available this shader program via glUseProgram()
             * Before to call the function, it checks the current shader in order 
             * to not call glUseProgram() while it isn't needed
             */ 
            virtual void useProgram();

        public:

            //Constructor with path to file
            Shader(std::string* pathToVertexFile, std::string* pathToFragmentFile);

            //Constructor with code already taken
            Shader(const char* vertexCode, const char* fragmentCode);

            unsigned int* getVBO();
            unsigned int* getVAO();
            unsigned int* getEBO();
            unsigned int* getVertexShader();
            unsigned int* getFragmentShader();
            unsigned int* getShaderProgram();

            float* getVertices();
            unsigned int getSizeVertices();
            void setVertices(float* _buffer, unsigned int _sizeBuffer);

            unsigned int* getIndices();
            unsigned int getSizeIndices();
            void setIndices(unsigned int* _buffer, unsigned int _sizeBuffer);

            static std::vector<unsigned int*>* getVBOs();
            static std::vector<unsigned int*>* getVAOs();
            static std::vector<unsigned int*>* getEBOs();
            static std::vector<unsigned int*>* getVertexShaders();
            static std::vector<unsigned int*>* getFragmentShaders();
            static std::vector<unsigned int*>* getShaderPrograms();

            //Free memory and close shader program
            //void free();
    };
    
}

#endif