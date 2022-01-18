#include "Matrix3.h"

jgl::Matrix3::Matrix3(float x1y1, float x1y2, float x1y3, float x2y1, float x2y2, float x2y3, float x3y1, float x3y2, float x3y3){
    this->matrix[0][0] = x1y1; this->matrix[0][1] = x1y2; this->matrix[0][2] = x1y3;
    this->matrix[1][0] = x2y1; this->matrix[1][1] = x2y2; this->matrix[1][2] = x2y3;
    this->matrix[2][0] = x3y1; this->matrix[2][1] = x3y2; this->matrix[2][2] = x3y3;
}
jgl::Matrix3::Matrix3(Matrix3* mat3d) : jgl::Matrix3(
    mat3d->matrix[0][0],  mat3d->matrix[0][1],  mat3d->matrix[0][2],
    mat3d->matrix[1][0],  mat3d->matrix[1][1],  mat3d->matrix[1][2],
    mat3d->matrix[2][0],  mat3d->matrix[2][1],  mat3d->matrix[2][2]){

}
jgl::Matrix3::Matrix3(std::string* fromString){

    std::string buffer = *fromString;
    for(int x = 0; x < 3; x++){

        std::string buffer1 = buffer.substr(0, buffer.find_first_of(';'));

        if(buffer.length() > buffer1.length()){
            buffer = buffer.substr(buffer1.length()+1, buffer.length());
        }

        for(int y = 0; y < 3; y++){
            int lastIndex = buffer1.find_first_of(',');
            float value = atof(buffer1.substr(0, lastIndex).c_str());
            buffer1 = buffer1.substr(lastIndex+1, buffer1.length());

            this->matrix[x][y] = value;
        }
    }
}
jgl::Matrix3::Matrix3(float yaw) : jgl::Matrix3(        
        cos(yaw), sin(yaw), 0,
        -sin(yaw), cos(yaw), 0,
        0, 0, 1){

}
jgl::Matrix3::Matrix3() : jgl::Matrix3::Matrix3(0, 0, 0, 
                                                    0, 0, 0, 
                                                    0, 0, 0){
}
jgl::Matrix3::Matrix3(float* values) : jgl::Matrix3::Matrix3(
        values[0], values[1], values[2],
        values[3], values[4], values[5],
        values[6], values[7], values[8] 
    ){
}
jgl::Matrix3::Matrix3(float yaw, jgl::Vector2f* position, float scale){
    this->setToTranslation(position);
    this->rotate(yaw);
    this->scale(scale, scale);
}
jgl::Matrix3::Matrix3(float yaw, jgl::Vector2f* position) : jgl::Matrix3(yaw, position->cpy()->vrs(), position->lenght()){

}


jgl::Matrix3* jgl::Matrix3::cpy(){
    return new jgl::Matrix3(this);
}



jgl::Matrix3* jgl::Matrix3::set(float* values){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = values[x*3 + y];
        }
    }

    return this;
}
jgl::Matrix3* jgl::Matrix3::set(Matrix3* mat3d){

    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = mat3d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix3* jgl::Matrix3::set(int x, int y, float value){
    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }else{
        this->matrix[x][y] = value;
    }

    return this;
}
jgl::Matrix3* jgl::Matrix3::setAll(float value){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = value;
        }
    }

    return this;
}



float jgl::Matrix3::get(int x, int y){

    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }else{
        return this->matrix[x][y];
    }
}



std::string* jgl::Matrix3::toString(){
    return new std::string(
        std::to_string(this->matrix[0][0]) + "," + std::to_string(this->matrix[0][1]) + "," + std::to_string(this->matrix[0][2]) + ";" + 
        std::to_string(this->matrix[1][0]) + "," + std::to_string(this->matrix[1][1]) + "," + std::to_string(this->matrix[1][2]) + ";" + 
        std::to_string(this->matrix[2][0]) + "," + std::to_string(this->matrix[2][1]) + "," + std::to_string(this->matrix[2][2]) + ";" 
    );
}



jgl::Matrix3* jgl::Matrix3::addAll(float value){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] += value;
        }
    }

    return this;
}
jgl::Matrix3* jgl::Matrix3::add(Matrix3* mat3d){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] += mat3d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix3* jgl::Matrix3::add(int x, int y, float value){

    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }

    this->matrix[x][y] += value;

    return this;
}



jgl::Matrix3* jgl::Matrix3::mulAll(float value){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] *= value;
        }
    }

    return this;
}
jgl::Matrix3* jgl::Matrix3::mul(Matrix3* mat3d){

    this->set( new jgl::Matrix3(
        matrix[0][0]*mat3d->matrix[0][0] + matrix[0][1]*mat3d->matrix[1][0] + matrix[0][2]*mat3d->matrix[2][0],
        matrix[0][0]*mat3d->matrix[0][1] + matrix[0][1]*mat3d->matrix[1][1] + matrix[0][2]*mat3d->matrix[2][1],
        matrix[0][0]*mat3d->matrix[0][2] + matrix[0][1]*mat3d->matrix[1][2] + matrix[0][2]*mat3d->matrix[2][2],

        matrix[1][0]*mat3d->matrix[0][0] + matrix[1][1]*mat3d->matrix[1][0] + matrix[1][2]*mat3d->matrix[2][0],
        matrix[1][0]*mat3d->matrix[0][1] + matrix[1][1]*mat3d->matrix[1][1] + matrix[1][2]*mat3d->matrix[2][1],
        matrix[1][0]*mat3d->matrix[0][2] + matrix[1][1]*mat3d->matrix[1][2] + matrix[1][2]*mat3d->matrix[2][2],

        matrix[2][0]*mat3d->matrix[0][0] + matrix[2][1]*mat3d->matrix[1][0] + matrix[2][2]*mat3d->matrix[2][0],
        matrix[2][0]*mat3d->matrix[0][1] + matrix[2][1]*mat3d->matrix[1][1] + matrix[2][2]*mat3d->matrix[2][1],
        matrix[2][0]*mat3d->matrix[0][2] + matrix[2][1]*mat3d->matrix[1][2] + matrix[2][2]*mat3d->matrix[2][2]
    ));

    return this;
}
jgl::Matrix3* jgl::Matrix3::mul(int x, int y, float value){

    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }

    this->matrix[x][y] = this->matrix[x][y] * value;

    return this;
}



float jgl::Matrix3::det(){

    return
        matrix[0][0]*matrix[1][1]*matrix[2][2] + 
        matrix[0][1]*matrix[1][2]*matrix[2][0] +
        matrix[0][2]*matrix[1][0]*matrix[2][1] -

        matrix[0][2]*matrix[1][1]*matrix[2][0] - 
        matrix[0][1]*matrix[1][0]*matrix[2][2] -
        matrix[0][0]*matrix[1][2]*matrix[2][1];
}



jgl::Matrix3* jgl::Matrix3::idt(){
    this->set(new Matrix3());
    this->set(0, 0, 1);
    this->set(1, 1, 1);
    this->set(2, 2, 1);
    return this;
}



jgl::Matrix3* jgl::Matrix3::inv(){
        if(this->det() != 0){
        float tmp;
        jgl::Matrix3* idt = (new jgl::Matrix3())->idt();

        //x0y0 as 1
        this->setIdentityMatrix(idt, 0);

        //x1y0 nullify
        this->substractRow(idt, 1, 0, 0);
        //x1y1 as 1
        this->setIdentityMatrix(idt, 1);

        //x2y0 nullify
        this->substractRow(idt, 2, 0, 0);
        //x2y1 nullify
        this->substractRow(idt, 2, 1, 1);
        //x2y2 as 1
        this->setIdentityMatrix(idt, 2); 

        /**
         * Let's manupulate top-right stair
         */

        //x1y2 nullify
        this->substractRow(idt, 1, 2, 2);

        //x0y2 nullify
        this->substractRow(idt, 0, 2, 2);
        //x0y1 nullify
        this->substractRow(idt, 0, 1, 1);

        return idt;
    }

    return nullptr;
}



jgl::Matrix3* jgl::Matrix3::rotate(float radians){
    return this->mul(new jgl::Matrix3(radians));
}
jgl::Matrix3* jgl::Matrix3::setToRotation(float radians){
    return this->set(new jgl::Matrix3(radians));
}
float jgl::Matrix3::getRotation(){

    float scalingFactor = this->getScale();

    if(asin(this->matrix[0][1]*(1/scalingFactor)) < 0){
        return M_PI*2 - acos(this->matrix[0][0]);
    }else{
        return acos(this->matrix[0][0]*(1/scalingFactor));
    }
}



jgl::Matrix3* jgl::Matrix3::scale(float x, float y){
    return this->mul(new jgl::Matrix3(x, 0, 0, 0, y, 0, 0, 0, 1));
}
jgl::Matrix3* jgl::Matrix3::scale(jgl::Vector2f* vec2f){
    return this->scale(vec2f->getX(), vec2f->getY());
}
float jgl::Matrix3::getScale(){
    return sqrt(pow(this->matrix[0][0],2) + pow(this->matrix[0][1],2));
}
jgl::Matrix3* jgl::Matrix3::setToScaling(float x, float y){
    return this->set(new jgl::Matrix3(x, 0, 0, 0, y, 0, 0, 0, 1));
}
jgl::Matrix3* jgl::Matrix3::setToScaling(jgl::Vector2f* vec2f){
    return this->setToScaling(vec2f->getX(), vec2f->getY());
}



jgl::Matrix3* jgl::Matrix3::translate(float x, float y){
    return this->mul(new jgl::Matrix3(1, 0, x, 0, 1, y, 0, 0, 1));
}
jgl::Matrix3* jgl::Matrix3::translate(jgl::Vector2f* vec2f){
    return this->translate(vec2f->getX(), vec2f->getY());
}
jgl::Vector2f* jgl::Matrix3::getTranslation(){
    return new jgl::Vector2f(this->matrix[0][2], this->matrix[1][2]);
}
jgl::Matrix3* jgl::Matrix3::setToTranslation(float x, float y){
    return this->set(new jgl::Matrix3(1, 0, x, 0, 1, y, 0, 0, 1));
}
jgl::Matrix3* jgl::Matrix3::setToTranslation(jgl::Vector2f* vec2f){
    return this->setToTranslation(vec2f->getX(), vec2f->getY());
}


/**
 * Here private methods for computing matrix
 * Check private area in header file for more info
 */ 


void jgl::Matrix3::setIdentityMatrix(jgl::Matrix3* &idt, int x){

    float tmp;
    /*
        Check if x,x is already 1. If it is 0, row will be swapped with the next one if the next one is not the third
    */
    if( (tmp = this->matrix[x][x]) != 0 && tmp != 1){
        tmp = this->matrix[x][x];
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] /= tmp;
            idt->matrix[x][y] /= tmp;
        }
    }else if(tmp == 0){
        //Swap
        for(int y = 0; y < 3; y++){
            tmp = this->matrix[x][y];
            this->matrix[x][y] = this->matrix[x+1][y];
            this->matrix[x+1][y] = tmp;

            tmp = idt->matrix[x][y];
            idt->matrix[x][y] = idt->matrix[x+1][y];
            idt->matrix[x+1][y] = tmp;
        }
    }
}

void jgl::Matrix3::substractRow(jgl::Matrix3* &idt, int x, int y, int row){

    float tmp;
    //Check if it is already 0
    if( (tmp = this->matrix[x][y]) != 0 ){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] -= tmp*this->matrix[row][y];
            idt->matrix[x][y] -= tmp*idt->matrix[row][y];
        }
    }
}