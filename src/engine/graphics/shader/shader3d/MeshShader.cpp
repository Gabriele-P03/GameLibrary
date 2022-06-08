#include "MeshShader.hpp"

jpl::MeshShader::MeshShader(std::string* pathToVertex, std::string* pathToFragment)
    : jpl::Shader(pathToVertex, pathToFragment){

    this->rotation = (new jgl::Matrix4())->idt();
    this->scale = (new jgl::Matrix4())->setToScale(1.0f, 1.0f, 1.0f, true);
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
        if(mesh->getIndices() != nullptr){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getSizeIndices() * sizeof(mesh->getIndices()), mesh->getIndices(), GL_STATIC_DRAW);
        }

        glBindVertexArray(0);
    }
}

void jpl::MeshShader::draw(jpl::Mesh* mesh, jgl::Matrix4* combined, float x, float y, float z){
    this->useProgram();

    jgl::Matrix4* transform = this->rotation->cpy()->mul(this->scale)->setToTranslation(x, y, z, false);
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "combined"), 1, GL_FALSE, &combined->matrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, 
        &transform->matrix[0][0]);

    this->bind(mesh);
    
    
    //As model which is not a cube, or kinda of, it hardly ever will use indices
    //We can check it via mesh->getIndices() != nullptr
    glBindVertexArray(*this->VAO);
    if(mesh->getIndices() != nullptr){  
        glDrawElements(GL_TRIANGLES, mesh->getSizeIndices(), GL_UNSIGNED_INT, (void*)0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, mesh->getSizeVertices());
    }
}