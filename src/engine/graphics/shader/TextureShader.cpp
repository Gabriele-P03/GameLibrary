#include "TextureShader.hpp"


jpl::TextureShader::TextureShader() : 
    jpl::TextureShader("shaders/vertex.vs", "shaders/fragment.fs"){
}

jpl::TextureShader::TextureShader(std::string vertexFilePath, std::string fragmentFilePath)
     : jpl::Shader(vertexFilePath, fragmentFilePath){

    this->_sizeVertices = 20;
    this->vertices = new float[this->_sizeVertices]{
        -1.0f, -1.0f, 0.0f,    0.0f, 1.0f,
        1.0f, -1.0f, 0.0f,    1.0f, 1.0f,           
        1.0f, 1.0f, 0.0f,     1.0f, 0.0f,    
        -1.0f, 1.0f, 0.0f,    0.0f, 0.0f
    };

    this->_sizeIndices = 6;
    this->indices = new unsigned int[this->_sizeIndices]{
        0, 1, 2,    //Front face
        0, 2, 3,
    };

    this->bind();
}


/**
 * Static fields are initialized before everything.
 * Shader generates new OpenGl's buffers, whose library needs to be initialized before.
 * Initialize a library before reltive static fields is not possible...
 * Then we need to define as nullptr the pointer, which will be redefined in the main function
 * 
 * Same thing for the TextShader static field
 */ 
jpl::TextureShader* jpl::TextureShader::TEXTURE_SHADER_DEFAULT = nullptr;