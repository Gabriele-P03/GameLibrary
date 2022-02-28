#include "Mesh.hpp"

jpl::Mesh::Mesh(float* vertices, unsigned int _sizeVertices, unsigned int* indices, unsigned int _sizeIndices){
    this->vertices = vertices;
    this->_sizeVertices = _sizeVertices;
    this->indices = indices;
    this->_sizeIndices = _sizeIndices;
}

float* jpl::Mesh::getVertices() const{return this->vertices;}
unsigned int jpl::Mesh::getSizeVertices() const{return this->_sizeVertices;}
unsigned int* jpl::Mesh::getIndices() const{return this->indices;}
unsigned int jpl::Mesh::getSizeIndices() const{return this->_sizeIndices;}

const jpl::Mesh* jpl::Mesh::CUBE = new jpl::Mesh( new float[40]{
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,   //Bottom-Left-Front
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,     //Bottom-Right-Front
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     //Top-Right-Front
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,     //Top-Left-Front

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,    //Bottom-Left-Back
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,     //Bottom-Right-Back
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f,      //Top-Right-Back
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f        //Top-Left-Back
}, 40, new unsigned int[36]{
    0, 1, 2, 0, 2, 3,   //Front
    4, 5, 6, 4, 6, 7,   //Back
    5, 6, 2, 5, 2, 1,   //Right
    4, 7, 3, 4, 3, 0,   //Left
    2, 6, 7, 2, 7, 3,   //Top
    1, 5, 4, 1, 4, 0    //Bottom
}, 36);
