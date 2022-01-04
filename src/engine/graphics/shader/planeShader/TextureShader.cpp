#include "TextureShader.hpp"


jpl::TextureShader::TextureShader() : 
    jpl::TextureShader(new std::string("shaders/texture2d/vertex.vs"), new std::string("shaders/texture2d/fragment.fs")){
}

jpl::TextureShader::TextureShader(std::string* vertexFilePath, std::string* fragmentFilePath) : jpl::Shader(vertexFilePath, fragmentFilePath){


    this->_sizeVertices = 20;
    this->vertices = new float[this->_sizeVertices]{
        -0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f,           
        0.5f, 0.5f, 0.0f,     1.0f, 0.0f,    
        -0.5f, 0.5f, 0.0f,    0.0f, 0.0f
    };

    this->_sizeIndices = 6;
    this->indices = new unsigned int[this->_sizeIndices]{
        0, 1, 2,    //Front face
        0, 2, 3,
    };

    this->rotation = (new jgl::Matrix4())->idt();
}



void jpl::TextureShader::draw(jpl::Texture* texture, int x, int y, int lastX, int lastY, int offsetX, int offsetY, int w, int h){

    this->calculateTextureCoords(x, y, lastX, lastY, offsetX, offsetY, w, h, texture->getWidth(), texture->getHeight());

    int currentVAO;
    glGetProgramiv(*this->shaderProgram, GL_ARRAY_BUFFER_BINDING, &currentVAO);
    if(currentVAO != *this->VAO){

        this->useProgram();

        //Before binding buffer(s), it's gonna binding array
        glBindVertexArray(*this->VAO);

        //Binding VBO and send vertices
        glBindBuffer(GL_ARRAY_BUFFER, *this->getVBO());
        glBufferData(GL_ARRAY_BUFFER, this->_sizeVertices * sizeof(vertices), vertices, GL_STATIC_DRAW);

        //Enabling coords on screen
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //Enabling texture coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //Binding EBO and send elements (indices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_sizeIndices * sizeof(indices), indices, GL_STATIC_DRAW);
    }

    texture->draw();
    glUniformMatrix4fv(glGetUniformLocation(*this->shaderProgram, "rotation"), 1, GL_FALSE, &this->rotation->matrix[0][0]);

    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void jpl::TextureShader::draw(jpl::Texture* texture){
    this->draw(texture, 0, 0, 0, 0, 0, 0, texture->getWidth(), texture->getHeight());
}
void jpl::TextureShader::draw(jpl::Texture* texture, int x, int y, int lastX, int lastY, bool flag){
    this->draw(texture, x, y, lastX, lastY, 0, 0, texture->getWidth(), texture->getHeight());
}
void jpl::TextureShader::draw(jpl::Texture* texture, int x, int y, bool flag){
    this->draw(texture, x, y, 0, 0, 0, 0, texture->getWidth(), texture->getHeight());
}
void jpl::TextureShader::draw(jpl::Texture* texuture, int offsetX, int offsetY, int w, int h){
    this->draw(texuture, 0, 0, 0, 0, offsetX, offsetY, w, h);
}
void jpl::TextureShader::draw(jpl::Texture* texuture, int w, int h){
    this->draw(texuture, 0, 0, 0, 0, 0, 0, w, h);
}


void jpl::TextureShader::calculateTextureCoords(int x, int y, int lastX, int lastY, int offsetX, int offsetY, int w, int h, int wT, int hT){
    int widthWindow, heightWindow;
    glfwGetWindowSize(glfwGetCurrentContext(), &widthWindow, &heightWindow);

    //UVs are store in an array different by the one of shader's coordinates
    this->vertices[18] = (float)offsetX/(float)wT;
    this->vertices[19] = (float)offsetY/(float)hT;

    this->vertices[3] = (float)offsetX/(float)wT;
    this->vertices[4] = this->vertices[19] + (float)h/(float)hT;

    this->vertices[8] = this->vertices[18] + (float)w/(float)wT; 
    this->vertices[9] = this->vertices[19] + (float)h/(float)hT;

    this->vertices[13] = this->vertices[18] + (float)w/(float)wT;
    this->vertices[14] = (float)offsetY/(float)hT;




    double startX = (double)(x - (double)widthWindow/2)/(double)((double)widthWindow/2); 
    double startY = (double)(y - (double)heightWindow/2)/(double)((double)heightWindow/2);

    double lX, lY;
    if(lastX <= 0){ //Means no zoom, then quad must be wrapped to texture width supplied
        //lX = startX - (double)(w - widthWindow/2)/(double)(widthWindow/2);
        lX = (double)(w - (double)widthWindow/2)/(double)((double)widthWindow/2);
    }

    if(lastY <= 0){
        //lY = startY - (double)(h - heightWindow/2)/(double)(heightWindow/2);
        lY = (double)(h - (double)heightWindow/2)/(double)((double)heightWindow/2);
    }

    double newX = startX - (startX - lX)/2;
    double newY = startY - (startY - lY)/2;
    
    double screenRatio = (double)widthWindow/(double)heightWindow;  
    double imageRatio = (double)wT/(double)hT;

    if(imageRatio < screenRatio){
        if(wT > hT)
            this->rotation->scale( 1/((double)wT/(double)hT), 1.0f, 1.0f);
        else if(wT < hT)
            this->rotation->scale( 1/((double)hT/(double)wT), 1.0f, 1.0f);
        else
            this->rotation->scale( 1/screenRatio, 1.0f, 1.0f);
    }else if(imageRatio > screenRatio){
        if(wT < hT)
            this->rotation->scale( 1.0f, 1/((double)hT/(double)wT),  1.0f);
        else if(wT > hT)
            this->rotation->scale( 1.0f, 1/((double)wT/(double)hT), 1.0f);
        else
            this->rotation->scale( 1.0f, 1/screenRatio, 1.0f);
    }
    this->rotation->translate(newX, newY, 0.0f);


}