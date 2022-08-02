#include "TextShader.hpp"

jpl::TextShader::TextShader() : jpl::TextShader("font/font.png", "shaders/vertex.vs", "shaders/fragment.fs"){
    this->loadFont(6, 16, 16, 1);
}
jpl::TextShader::TextShader(std::string pathToFont) : jpl::TextShader(
    pathToFont, "shaders/vertex.vs", "shaders/fragment.fs"){

} 
jpl::TextShader::TextShader(std::string pathToVertex, std::string pathToFragment) : jpl::TextShader(
        *getInternalPath("font/font.png"), pathToVertex, pathToFragment){

} 

jpl::TextShader::TextShader(std::string pathToFont, std::string pathToVertex, std::string pathToFragment) :
    jpl::TextureShader(pathToVertex, pathToFragment) {

    this->font = new jpl::Texture(pathToFont, false);
    glBlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnablei(GL_BLEND, 0);
}      

void jpl::TextShader::loadFont(int rows, int cols, int size, int offset){

    if(this->font != nullptr){
            
        this->size = size;
        this->offset = offset;

            this->chars = new jpl::TextShader::Characters[rows*cols];

            for(int x = 0; x < rows; x++){
                for(int y = 0; y < cols; y++){
                    this->chars[x*cols + y].x = offset * (y+1) + y * size;
                    this->chars[x*cols + y].y = offset * (x+1) + x * size; 
                }
            }
    }else{
        jpl::Logger::INSTANCE->print("Null font to load...");
        exit(-1);
    }
}

void jpl::TextShader::setCombinedMatrix(glm::mat4 combinedMatrix){
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "combined"), 1, GL_FALSE, glm::value_ptr(combinedMatrix));
}


/**
 * Static fields are initialized before everything.
 * Shader generates new OpenGl's buffers, whose library needs to be initialized before.
 * Initialize a library before reltive static fields is not possible...
 * Then we need to define as nullptr the pointer, which will be redefined in the main function
 * 
 * Same thing for the TextureShader static field
 */ 
jpl::TextShader* jpl::TextShader::TEXT_SHADER_DEFAULT = nullptr;