#include "TextShader.hpp"

jpl::TextShader::TextShader() : jpl::TextShader(
    new std::string("font/font.png"),
    new std::string("shaders/text/vertex.vs"),
    new std::string("shaders/text/fragment.fs")){

    this->loadFont(11, 11, 32, 1);
}
jpl::TextShader::TextShader(std::string* pathToFont) : jpl::TextShader(
    pathToFont,
    new std::string("shaders/text/vertex.vs"),
    new std::string("shaders/text/fragment.fs")){

} 
jpl::TextShader::TextShader(std::string* pathToVertex, std::string* pathToFragment) : jpl::TextShader(
        getInternalPath(new std::string("font/font.png")),
        pathToVertex, pathToFragment){

} 

jpl::TextShader::TextShader(std::string* pathToFont, std::string* pathToVertex, std::string* pathToFragment) :
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

void jpl::TextShader::render(std::string* text, int x, int y){

    for(int i = 0; i < text->length(); i++){

        char buffer = text->at(i);
        int dec = (int)buffer;

        if(dec >= 33 || dec <= 126){
            this->draw(this->font, x+size*i, y, size, size, this->chars[dec-33].x, this->chars[dec-33].y, size, size);
        }
    }
}


//jpl::TextShader* jpl::TextShader::TEXT_SHADER_DEFAULT = new jpl::TextShader();