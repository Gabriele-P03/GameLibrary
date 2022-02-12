#include "MeshShader.hpp"

jpl::MeshShader::MeshShader(std::string* pathToVertex, std::string* pathToFragment)
    : jpl::Shader(pathToVertex, pathToFragment){

}

void jpl::MeshShader::draw() {
    //Override this method in a sub-class
    //You should call bind(jpl::Mesh*) inside this
    //Then bind VAO and then call glDrawElements
}

void jpl::MeshShader::bind(const jpl::Mesh* mesh){

    //Check if this shader's objects are already bind
    int currentVAO = 0;
    glGetProgramiv(*this->shaderProgram, GL_ARRAY_BUFFER_BINDING, &currentVAO);
    if(currentVAO != *this->VAO){

        //Before binding buffer(s), it's gonna binding array
        glBindVertexArray(*this->VAO);

        //Binding VBO and send vertices
        glBindBuffer(GL_ARRAY_BUFFER, *this->VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->getSizeVertices() * sizeof(mesh->getVertices()), mesh->getVertices(), GL_STATIC_DRAW);

        //Enabling coords on screen
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //Enabling texture coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //Binding EBO and send elements (indices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getSizeIndices() * sizeof(mesh->getIndices()), mesh->getIndices(), GL_STATIC_DRAW);
    
        glBindVertexArray(0);
    }
}