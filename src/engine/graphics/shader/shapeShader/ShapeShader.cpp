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
        std::cout<<"Error ShapeShader: begin() already called"<<std::endl;
        exit(-1);
    }else{
        if(this->vertices != nullptr)
            delete this->vertices;
        if(this->indices != nullptr)
            delete this->indices;
        this->working = true;
        this->shape_type = shape_type;
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
            //It is gonna leave empty 'cause lines does not need elements for being rendered
            _sizeIndices = 0;
            indices = new unsigned int;
        break;

        case 1:
            _sizeVertices = 12;
            vertices = new float[_sizeVertices]{-0.5f, -0.5f, 0.0f, 
                                                0.5f, -0.5f, 0.0f, 
                                                0.0f, 0.5f, 0.0f};
            _sizeIndices = 3;
            indices = new unsigned int[_sizeIndices]{0, 1, 2};
        break;

        case 2:
            _sizeVertices = 16;
            vertices = new float[_sizeVertices]{-0.5f, -0.5f, 0.0f, 
                                                0.5f, -0.5f, 0.0f, 
                                                0.5f, 0.5f, 0.0f,
                                                -0.5f, 0.5f, 0.0f};
            _sizeIndices = 6;
            indices = new unsigned int[_sizeIndices]{0, 1, 2, 0, 2, 3};
        break;
        
        case 3:
            //Let's looking for a way to render a circle with GLSL
        break;
    
        default:
        break;
    }
}


void jpl::ShapeShader::drawLine(int x, int y, float length, float* colors){

    int w, h;
    glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);

    this->checkBeginCall(SHAPE_LINE);
    this->transform->setToScale(length/(float)w, 1.0f, 1.0f, true);
    float* coords = jplOpenGlCoords(x, y);
    this->transform->translate(coords[0], coords[1], 0.0f);
    this->useProgram();
    glUniform4f(glGetUniformLocation(*this->getShaderProgram(), "cols"), colors[0], colors[1], colors[2], colors[3]);
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, &this->transform->matrix[0][0]);
    this->bind();
    glBindVertexArray(*this->VAO);
    glDrawArrays(GL_LINES, 0, this->_sizeVertices);
}


void jpl::ShapeShader::drawQuad(int x, int y, float length, float* colors){

    this->checkBeginCall(SHAPE_QUAD);
    int w, h;
    glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
    this->transform->setToScale(length/(float)w, length/(float)h, 1.0f, true);
    float* coords = jplOpenGlCoords(x, y);
    this->transform->translate(coords[0], coords[1], 0.0f);
    this->useProgram();
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, &this->transform->matrix[0][0]);
    this->bindAndDraw(colors);
}
void jpl::ShapeShader::drawTriangle(int x, int y, float length, float* colors){

    this->checkBeginCall(SHAPE_TRIANGLE);
    int w, h;
    glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
    this->transform->setToScale(length/(float)w, length/(float)h, 1.0f, true);
    float* coords = jplOpenGlCoords(x, y);
    this->transform->translate(coords[0], coords[1], 0.0f);
    this->useProgram();
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, &this->transform->matrix[0][0]);
    this->bindAndDraw(colors);
}

inline void jpl::ShapeShader::bindAndDraw(float* colors){

    glUniform4f(glGetUniformLocation(*this->getShaderProgram(), "cols"), colors[0], colors[1], colors[2], colors[3]);
    this->bind();
    glBindVertexArray(*this->VAO);
    glDrawElements(GL_TRIANGLES, this->_sizeIndices, GL_UNSIGNED_INT, (void*)0);
}


void jpl::ShapeShader::checkBeginCall(SHAPE_TYPE shape_type){

    if(!this->working){
        std::cout<<"Error ShapeShader: you're trying to render without have called ShapeShader#begin() before..."<<std::endl;
        exit(-1);
    }else{
        if(this->shape_type != shape_type){
            std::cout<<"Error ShapeRender (" + std::to_string(this->shape_type) + "): trying to render another shape (" + std::to_string(shape_type) + ")"<<std::endl;
            exit(-1);
        }
    }
}

jpl::ShapeShader::SHAPE_TYPE jpl::ShapeShader::getShapeType(){ return this->shape_type; }