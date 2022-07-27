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
 * This framework has already some ready shader:
 *  - ModelShader for rendering 3D
 *  - TextureShader for rendering 2D stuff
 *  - TextShader for rendering text either in 2D or 3D context 
 * 
 * If you're gonna calling render/draw method, you must know that useProgram() is called by them,
 * but if you're sending combined matrix to the shader program, before have done the call to the
 * render/draw method, you should call useProgram() before.
 * 
 * @author Gabriele-P03
 */ 

#ifndef SHADER_JPL_H
#define SHADER_JPL_H

#include <iostream>
#include <string>
#include "../../../files/Files.h"
#include <fstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/gtx/euler_angles.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../math/JMath.hpp"


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
             *  Bind buffers calling bindVBO(), bindEBO() and vertexAttrib()
            */  
            inline virtual void bind(){
                //Check if this shader's objects are already bind
                int currentVAO;
                glGetProgramiv(*this->shaderProgram, GL_ARRAY_BUFFER_BINDING, &currentVAO);
                if(currentVAO != *this->VAO){

                    //Before binding buffer(s), it's gonna binding array
                    glBindVertexArray(*this->VAO);

                    this->bindVBO();
                    this->bindEBO();
                    this->vertexAttrib();

                    glBindVertexArray(0);
                }
            }

            /**
             * Bind VBO.
             * You should never call this func, it is already done by bind().
             * But you can override it, if you need it  
             */ 
            inline virtual void bindVBO(){
                glBindBuffer(GL_ARRAY_BUFFER, *this->VBO);
                glBufferData(GL_ARRAY_BUFFER, this->_sizeVertices * sizeof(vertices), vertices, GL_STATIC_DRAW);
            }

            /**
             * Bind EBO
             * You should never call this func, it is already done by bind().
             * But you can override it, if you need it  
             */ 
            inline virtual void bindEBO(){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *this->EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_sizeIndices * sizeof(indices), indices, GL_STATIC_DRAW);
            }

            /**
             * Make the calls to glVertexAttribArray() and enable it
             * You should never call this func, it is already done by bind().
             * But you can override it, if you need it 
             */ 
            inline virtual void vertexAttrib(){
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
            }


            /*
                Draw the triangles which compose this shader.
                First call glUseProgram() in order to set this shader available for pipeline,
                then call glBindVertexArray(VAO) and then draw elements via glDrawArrays()
            */
            inline virtual void draw(){
                this->useProgram();
                this->bind();
                glBindVertexArray(*this->VAO);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
            }

            /**
             * Called by constrctor, it initializes vectors
             */ 
            virtual void initializeVectors();

            glm::vec3 right, up;

        public:
            
            glm::mat4 rotation;
            glm::vec3 scale, translation; 

            //Constructor with path to file
            Shader(std::string pathToVertexFile, std::string pathToFragmentFile);

            //Constructor with code already taken
            Shader(const char* vertexCode, const char* fragmentCode);

            /**
             * It creates a new transformation matrix and pushes it to OpenGL.
             * Since this shader has been performed to work with uniform variable, this 
             * function is not called automatically.
             */ 
            virtual void pushMatrixTransformation();

            /**
             * After have changed the rotation vector, you should call this method in order to 
             * update also up and right
             */ 
            virtual void updateUpAndRight();

            /**
             * Set available this shader program via glUseProgram()
             * Before to call the function, it checks the current shader in order 
             * to not call glUseProgram() while it isn't needed
             */ 
            inline virtual void useProgram(){
                //Retrieve the current shader program in order to not call glUseProgram()
                int currentId;
                glGetIntegerv(GL_CURRENT_PROGRAM, &currentId);

                if(currentId != *this->shaderProgram)
                    glUseProgram(*this->shaderProgram);
            }


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
    };
    
}

#endif