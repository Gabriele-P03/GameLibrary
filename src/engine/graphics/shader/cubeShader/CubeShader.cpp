#include "CubeShader.hpp"

jpl::CubeShader::CubeShader() : jpl::Shader::Shader(new std::string("shaders/cube/vertexCube.vs"), new std::string("shaders/cube/fragmentCube.fs")){

    this->_sizeVertices = 24;
    this->vertices = new float[this->_sizeVertices]{
        -0.5f, 0.5f, 0.5f,     //Top-Left-Front
        -0.5f, -0.5f, 0.5f,    //Bottom-Left-Front 
        0.5f, 0.5f, 0.5f,      //Top-Right-Front
        0.5f, -0.5f, 0.5f,     //Bottom-Right-Front  

        -0.5f, 0.5f, -0.5f,     //Top-Left-Back
        -0.5f, -0.5f, -0.5f,    //Bottom-Left-Back 
        0.5f, 0.5f, -0.5f,      //Top-Right-Back
        0.5f, -0.5f, -0.5f,     //Bottom-Right-Back  
    };

    this->_sizeIndices = 36;
    this->indices = new unsigned int[this->_sizeIndices]{
        0, 1, 2,    //Front face
        1, 2, 3,

        4, 5, 6,    //Back Face
        5, 6, 7,

        0, 1, 4,    //Left Face
        1, 4, 5,

        2, 3, 6,    //Right Face
        3, 7, 6,

        0, 2, 4,    //Top Face
        2, 4, 6,

        1, 3, 5,    //Bottom Face
        3, 5, 7
    };
}