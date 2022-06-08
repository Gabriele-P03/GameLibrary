#include "CubeShader.hpp"

jpl::CubeShader::CubeShader() : jpl::MeshShader::MeshShader(new std::string("shaders/cube/vertexCube.vs"), new std::string("shaders/cube/fragmentCube.fs")){

    int widthWindow, heightWindow;
    glfwGetWindowSize(glfwGetCurrentContext(), &widthWindow, &heightWindow);
}


void jpl::CubeShader::draw(jgl::Matrix4* combined, float x, float y, float z){
    jpl::MeshShader::draw(jpl::Mesh::CUBE, combined, x, y, z);
}