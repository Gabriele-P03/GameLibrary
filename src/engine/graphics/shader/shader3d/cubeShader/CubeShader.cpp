#include "CubeShader.hpp"

jpl::CubeShader::CubeShader() : jpl::MeshShader::MeshShader(new std::string("shaders/cube/vertexCube.vs"), new std::string("shaders/cube/fragmentCube.fs")){

    int widthWindow, heightWindow;
    glfwGetWindowSize(glfwGetCurrentContext(), &widthWindow, &heightWindow);
    //this->scale = (new jgl::Matrix4())->setToScale((float)heightWindow/(float)widthWindow, 1.0f, 1.0f, true);
    this->scale = (new jgl::Matrix4())->idt();
    this->rotation = (new jgl::Matrix4())->idt();
    this->translating = (new jgl::Matrix4())->idt();

}

void jpl::CubeShader::draw(jgl::Matrix4* combined, float x, float y, float z){
    this->useProgram();
    this->translating->setToTranslation(x, y, z, true);
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "combined"), 1, GL_FALSE, &combined->matrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, 
        &(this->rotation->cpy()->mul(this->scale)->mul(this->translating))->matrix[0][0]);

    this->bind(jpl::Mesh::CUBE);
    glBindVertexArray(*this->VAO);
    
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

void jpl::CubeShader::draw(){

}