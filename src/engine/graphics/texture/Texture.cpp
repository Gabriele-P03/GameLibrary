#include "Texture.hpp"

jpl::Texture::Texture(std::string* path){

    this->img = new jpl::Texture::image;

    unsigned error_t = lodepng::decode(this->img->data, this->img->w, this->img->h, getInternalPath(path)->c_str());

    if(error_t){
        std::cout<<"Texture loading error "<<error_t<<": "<<lodepng_error_text(error_t)<<std::endl;
    }else{
        this->genTexture();
    }
}


void jpl::Texture::genTexture(){
    textureIDs.push_back(new unsigned int);
    this->img->textureID = textureIDs.at(textureIDs.size()-1);
    glGenTextures(1, this->img->textureID);
}



void jpl::Texture::draw(){

//    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *this->getTextureID());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    unsigned char* byte = &getData()->at(0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->getWidth(), this->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, byte);
}



unsigned int jpl::Texture::getHeight(){return this->img->h;}
unsigned int jpl::Texture::getWidth(){return this->img->w;}
unsigned int* jpl::Texture::getTextureID(){return this->img->textureID;}
std::vector<unsigned char>* jpl::Texture::getData(){return &this->img->data;}

std::vector<unsigned int*> jpl::Texture::textureIDs;