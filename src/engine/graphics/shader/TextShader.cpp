#include "TextShader.hpp"

jpl::TextShader::TextShader() : jpl::TextShader("font/font.png", "shaders/vertex.vs", "shaders/fragment.fs"){
    this->loadFont(11, 11, 32, 1);
}
jpl::TextShader::TextShader(std::string pathToFont) : jpl::TextShader(
    pathToFont, "shaders/vertex.vs", "shaders/fragment.fs"){

} 
jpl::TextShader::TextShader(std::string pathToVertex, std::string pathToFragment) : jpl::TextShader(
        *getInternalPath("font/font.png"), pathToVertex, pathToFragment){

} 

jpl::TextShader::TextShader(std::string pathToFont, std::string pathToVertex, std::string pathToFragment) :
    jpl::TextureShader(pathToVertex, pathToFragment) {

    this->font = new jpl::Texture(pathToFont);
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
        std::cout<<"Null font to load...\n";
        exit(-1);
    }
}

void jpl::TextShader::render(std::string text, int x, int y){
    this->render(text, x, y, 1.0f, 1.0f, 1.0f, 1.0f);
}

void jpl::TextShader::render(std::string text, int x, int y, float red, float green, float blue, float alpha){
    this->render(text, x, y, new float[4]{red, green, blue, alpha});
}

void jpl::TextShader::render(std::string text, int x, int y, float* colors){

    this->useProgram();

    glUniform4f(glGetUniformLocation(*this->getShaderProgram(), "cols"), colors[0], colors[1], colors[2], colors[3]);
    
    if(!text.empty()){
        if(text.length() > 0){
            for(int i = 0; i < text.length(); i++){

                char buffer = text.at(i);
                int dec = (int)buffer;

                if(dec >= 33 || dec <= 126){
                    this->setCombinedMatrix(glm::mat4(1.0f));
                    this->draw(this->font, x+size*i, y, size, size, this->chars[dec-33].x, this->chars[dec-33].y, size, size);
                }
            }
        }
    }
}

void jpl::TextShader::setCombinedMatrix(glm::mat4 combinedMatrix){
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "combined"), 1, GL_FALSE, glm::value_ptr(combinedMatrix));
}

int jpl::TextShader::getFontSize(){return this->size;}

/**
 * Static fields are initialized before everything.
 * Shader generates new OpenGl's buffers, whose library needs to be initialized before.
 * Initialize a library before reltive static fields is not possible...
 * Then we need to define as nullptr the pointer, which will be redefined in the main function
 * 
 * Same thing for the TextureShader static field
 */ 
jpl::TextShader* jpl::TextShader::TEXT_SHADER_DEFAULT = nullptr;