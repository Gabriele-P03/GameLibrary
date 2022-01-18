#include "ShapeShader.hpp"

jpl::ShapeShader::ShapeShader(jpl::ShapeShader::SHAPE_TYPE shape_type) : jpl::Shader(
        new std::string("shaders/text/vertex.vs"),
        new std::string("shaders/text/fragment.fs")){

    this->shape_type = shape_type;

    this->transform = (new jgl::Matrix4())->idt();
}


void jpl::ShapeShader::begin(){
    this->begin(SHAPE_QUAD);
}
void jpl::ShapeShader::begin(SHAPE_TYPE shape_type){

}

float* jpl::ShapeShader::getShapeVertices(SHAPE_TYPE shape_type, int &size){

    switch (shape_type)
    {
        case 0:
            size = 4;
            return new float[4]{-0.5f, 0.0f, 0.5f, 0.0f};
        break;

        case 1:
            size = 6;
            return new float[6]{-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
        break;

        case 2:
            size = 8;
            return new float[8]{-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
        break;
        
        case 3:
            size = 8;
            return new float[8]{-0.5f, -0.25f, 0.5f, -0.25f, 0.5f, 0.25f, -0.5f, 0.25f};
        break;

        case 4:
            size = 8;
            return new float[8]{-0.5f, -0.25f, 0.5f, -0.25f, 0.5f, 0.25f, -0.5f, 0.25f};
        break;
    
        default:
        break;
    }
}