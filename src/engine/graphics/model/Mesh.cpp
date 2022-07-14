#include "Mesh.hpp"

jpl::Mesh::Mesh(float* vertices, unsigned int _sizeVertices, unsigned int* indices, unsigned int _sizeIndices){
    this->vertices = vertices;
    this->_sizeVertices = _sizeVertices;
    this->indices = indices;
    this->_sizeIndices = _sizeIndices;
}

jpl::Mesh::Mesh(std::vector<float*> vertices){
    this->vertices = new float[vertices.size()];
    for(int i = 0; i < vertices.size(); i++){
        this->vertices[i] = *vertices[i];
    }

    this->_sizeVertices = vertices.size();

    this->indices = nullptr;
    this->_sizeIndices = 0;
}

float* jpl::Mesh::getVertices() const{return this->vertices;}
unsigned int jpl::Mesh::getSizeVertices() const{return this->_sizeVertices;}
unsigned int* jpl::Mesh::getIndices() const{return this->indices;}
unsigned int jpl::Mesh::getSizeIndices() const{return this->_sizeIndices;}
unsigned int jpl::Mesh::getVerticesPerFace(){return this->verticesPerFace;}
jpl::Mesh* jpl::Mesh::setVerticesPerFace(unsigned int verticesPerFace){this->verticesPerFace = verticesPerFace; return this;}

jpl::Mesh* jpl::Mesh::CUBE = new jpl::Mesh(new float[40]{

    //Back 
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,    
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,     
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 

    //Front 
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
}, 40, new unsigned int[36]{

    0, 1, 2, 0, 2, 3,   //back
    4, 5, 6, 4, 6, 7,   //front
    0, 3, 4, 3, 4, 7,   //left
    1, 2, 6, 1, 6, 5,   //right
    2, 3, 6, 3, 6, 7,   //up
    0, 1, 4, 1, 4, 5    //bottom
}, 36);

jpl::Mesh* jpl::Mesh::FACED_CUBE = new jpl::Mesh( new float[120]{

    //Back 
    -0.5f, -0.5f, -0.5f, 0.1666f, 0.0f,   
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,    
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,     
    -0.5f, 0.5f, -0.5f, 0.1666f, 1.0f, 

    //Front 
    -0.5f, -0.5f, 0.5f, 0.1666f, 0.0f,   
    0.5f, -0.5f, 0.5f, 0.3332f, 0.0f,    
    0.5f, 0.5f, 0.5f, 0.3332f, 1.0f,     
    -0.5f, 0.5f, 0.5f, 0.1666f, 1.0f,     

    //Right
    0.5f, -0.5f, -0.5f, 0.3332f, 0.0f,    
    0.5f, 0.5f, -0.5f, 0.3332f, 1.0f,    
    0.5f, 0.5f, 0.5f, 0.4998f, 1.0f,      
    0.5f, -0.5f, 0.5f, 0.4998f, 0.0f,

    //Left
    -0.5f, -0.5f, -0.5f, 0.6664f, 0.0f,    
    -0.5f, 0.5f, -0.5f, 0.6664f, 1.0f,    
    -0.5f, 0.5f, 0.5f, 0.4998f, 1.0f,      
    -0.5f, -0.5f, 0.5f, 0.4998f, 0.0f,

    //Up
    -0.5f, 0.5f, -0.5f, 0.6664, 1.0f,
    0.5f, 0.5f, -0.5f, 0.8330f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.8330f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.66640f, 0.0f, 

    //Bottom
    -0.5f, -0.5f, -0.5f, 0.8330f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.9996f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.9996f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.8330f, 1.0f     

}, 120, new unsigned int[36]{
    0, 1, 2, 0, 2, 3,       //Front
    4, 5, 6, 4, 6, 7,       //Back
    8, 9, 10, 8, 10, 11,    //Left
    12, 13, 14, 12, 14, 15, //Right
    16, 17, 18, 16, 18, 19, //Up
    20, 21, 22, 20, 22, 23  //Bottom
    
}, 36);


