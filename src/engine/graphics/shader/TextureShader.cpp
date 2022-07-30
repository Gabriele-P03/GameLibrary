#include "TextureShader.hpp"


jpl::TextureShader::TextureShader() : 
    jpl::TextureShader("shaders/vertex.vs", "shaders/fragment.fs"){
}

jpl::TextureShader::TextureShader(std::string vertexFilePath, std::string fragmentFilePath) : jpl::Shader(vertexFilePath, fragmentFilePath){

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
}



void jpl::TextureShader::draw(jpl::Texture* texture, float x, float y, float z, int widthX, int heightY, int offsetX, int offsetY, int w, int h){

    this->calculateTextureCoords(x, y, z, widthX, heightY, offsetX, offsetY, w, h, texture->getWidth(), texture->getHeight());

    this->useProgram();

    int currentVAO;
    glGetProgramiv(*this->shaderProgram, GL_ARRAY_BUFFER_BINDING, &currentVAO);
    if(currentVAO != *this->VAO){

        //Before binding buffer(s), it's gonna binding array
        glBindVertexArray(*this->VAO);

        this->bindVBO();
        this->vertexAttrib();
        //Binding EBO and send elements (indices)
        this->bindEBO();
    }
    this->pushMatrixTransformation();
    texture->draw();
    glDrawElements(GL_TRIANGLES, this->_sizeIndices, GL_UNSIGNED_INT, (void*)0);
}

void jpl::TextureShader::draw(jpl::Texture* texture){
    this->draw(texture, 0, 0, 0, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight());
}
void jpl::TextureShader::draw(jpl::Texture* texture, float x, float y, float z, int lastX, int lastY, bool flag){
    this->draw(texture, x, y, z, lastX, lastY, 0, 0, texture->getWidth(), texture->getHeight());
}
void jpl::TextureShader::draw(jpl::Texture* texture, float x, float y, float z, bool flag){
    this->draw(texture, x, y, z, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(), texture->getHeight());
}
void jpl::TextureShader::draw(jpl::Texture* texuture, int offsetX, int offsetY, int w, int h){
    this->draw(texuture, 0, 0, 0, w, h, offsetX, offsetY, w, h);
}
void jpl::TextureShader::draw(jpl::Texture* texuture, int w, int h){
    this->draw(texuture, 0, 0, 0, w, h, 0, 0, w, h);
}

void jpl::TextureShader::vertexAttrib(){
    //Enabling coords on screen
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Enabling texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void jpl::TextureShader::calculateTextureCoords(

    float x, float y, float z, int widthX, int heightY, 
    int offsetX, int offsetY, int w, int h, int wT, int hT)

{

    int widthWindow = jpl::WindowSize::INSTANCE.w, heightWindow = jpl::WindowSize::INSTANCE.h;

    //UVs are store in an array different by the one of shader's coordinates
    this->vertices[18] = (float)offsetX/(float)wT;
    this->vertices[19] = (float)offsetY/(float)hT;

    this->vertices[3] = (float)offsetX/(float)wT;
    this->vertices[4] = this->vertices[19] + (float)h/(float)hT;

    this->vertices[8] = this->vertices[18] + (float)w/(float)wT; 
    this->vertices[9] = this->vertices[19] + (float)h/(float)hT;

    this->vertices[13] = this->vertices[18] + (float)w/(float)wT;
    this->vertices[14] = (float)offsetY/(float)hT;

    float widthRatio = (float)widthX/(float)widthWindow;
    float heightRatio = (float)heightY/(float)heightWindow;
    /*
    float widthRatio = (float)widthX/(float)wT;
    widthRatio *= w;
    widthRatio /= widthWindow;

    float heightRatio = (float)heightY/(float)hT;
    heightRatio *= h;
    heightRatio /= heightWindow;
    */

    float newX = -1.0f + 2.0f * ( (float)(x+widthX/2.0f)/(float)widthWindow ),
        newY = -1.0f + 2.0f * ( (float)(y+heightY/2.0f)/(float)heightWindow );

    /*
        As already known OpenGl works in range [-1; +1]. Now, considering that most of monitors is not
        a quad, we need to scale down x and y as the texture supplies.
        Do not care if your texture width is greater than window's; It will do it
    */
    this->scale = glm::vec3(
                (wT < widthWindow ?  widthRatio : 1/widthRatio), 
                (hT < heightWindow ? heightRatio : 1/heightRatio),
                 1.0f);

    //float tmpX = -1.0f + ((float)widthX/2.0f)/(float)widthWindow;
    this->translation = glm::vec3(newX, newY, z);
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