#include "ShapeShader.hpp"

jpl::ShapeShader::ShapeShader() : jpl::Shader(
        new std::string("shaders/text/vertex.vs"),
        new std::string("shaders/text/fragment.fs")){

    this->transform = (new jgl::Matrix4())->idt();
}


void jpl::ShapeShader::begin(){
    this->begin(SHAPE_QUAD);
}
void jpl::ShapeShader::begin(SHAPE_TYPE shape_type){

    if(this->working){
        delete this->vertices;
        delete this->indices;
    }else{
        this->working = true;
    }

    this->getShapeVertices(shape_type, this->vertices, this->_sizeVertices, this->indices, this->_sizeIndices);
}


void jpl::ShapeShader::end(){
    this->working = false;
}


void jpl::ShapeShader::getShapeVertices(SHAPE_TYPE shape_type, float* &vertices, unsigned int &_sizeVertices, unsigned int* &indices, unsigned int &_sizeIndices){

    switch (shape_type)
    {
        case 0:
            _sizeVertices = 6;
            vertices = new float[_sizeVertices]{-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f};
        break;

        case 1:
            _sizeVertices = 12;
            vertices = new float[_sizeVertices]{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
            _sizeIndices = 3;
            indices = new unsigned int[_sizeIndices]{0, 1, 2};
        break;

        case 2:
            _sizeVertices = 15;
            vertices = new float[_sizeVertices]{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f};
            _sizeIndices = 6;
            indices = new unsigned int[_sizeIndices]{0, 1, 2, 0, 1, 3};
        break;
        
        case 3:
            //Let's looking for a way to render a circle with GLSL
        break;
    
        default:
        break;
    }
}


void jpl::ShapeShader::drawLine(int x, int y, float length, float red, float green, float blue, float alpha){

    this->checkBeginCall();
    this->bind();
    glBindVertexArray(*this->VAO);
    glDrawElements(GL_LINE, this->_sizeIndices, GL_UNSIGNED_INT, (void*)0);
}


void jpl::ShapeShader::checkBeginCall(){

    if(!this->working){
        std::cout<<"Error ShapeShader: you're trying to render without have called ShapeShader#begin() before..."<<std::endl;
        exit(-1);
    }
}

jpl::ShapeShader::SHAPE_TYPE jpl::ShapeShader::getShapeType(){ return this->shape_type; }