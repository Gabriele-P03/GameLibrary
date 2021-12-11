#include "Matrix3d.h"

jgl::Matrix3d::Matrix3d(double x1y1, double x1y2, double x1y3, double x2y1, double x2y2, double x2y3, double x3y1, double x3y2, double x3y3){
    this->matrix[0][0] = x1y1; this->matrix[0][1] = x1y2; this->matrix[0][2] = x1y3;
    this->matrix[1][0] = x2y1; this->matrix[1][1] = x2y2; this->matrix[1][2] = x2y3;
    this->matrix[2][0] = x3y1; this->matrix[2][1] = x3y2; this->matrix[2][2] = x3y3;
}
jgl::Matrix3d::Matrix3d(Matrix3d* mat3d) : jgl::Matrix3d(
    mat3d->matrix[0][0],  mat3d->matrix[0][1],  mat3d->matrix[0][2],
    mat3d->matrix[1][0],  mat3d->matrix[1][1],  mat3d->matrix[1][2],
    mat3d->matrix[2][0],  mat3d->matrix[2][1],  mat3d->matrix[2][2]){

}
jgl::Matrix3d::Matrix3d(std::string* fromString){

    std::string buffer = *fromString;
    for(int x = 0; x < 3; x++){

        std::string buffer1 = buffer.substr(0, buffer.find_first_of(';'));

        if(buffer.length() > buffer1.length()){
            buffer = buffer.substr(buffer1.length()+1, buffer.length());
        }

        for(int y = 0; y < 3; y++){
            int lastIndex = buffer1.find_first_of(',');
            double value = atof(buffer1.substr(0, lastIndex).c_str());
            buffer1 = buffer1.substr(lastIndex+1, buffer1.length());

            this->matrix[x][y] = value;
        }
    }
}
jgl::Matrix3d::Matrix3d(double yaw) : jgl::Matrix3d(        
        cos(yaw), sin(yaw), 0,
        -sin(yaw), cos(yaw), 0,
        0, 0, 1){

}
jgl::Matrix3d::Matrix3d() : jgl::Matrix3d::Matrix3d(0, 0, 0, 
                                                    0, 0, 0, 
                                                    0, 0, 0){
}
jgl::Matrix3d::Matrix3d(double* values) : jgl::Matrix3d::Matrix3d(
        values[0], values[1], values[2],
        values[3], values[4], values[5],
        values[6], values[7], values[8] 
    ){
}
jgl::Matrix3d::Matrix3d(double yaw, jgl::Vector2d* position, double scale){
    this->setToTranslation(position);
    this->rotate(yaw);
    this->scale(scale, scale);
}
jgl::Matrix3d::Matrix3d(double yaw, jgl::Vector2d* position) : jgl::Matrix3d(yaw, position->cpy()->vrs(), position->lenght()){

}


jgl::Matrix3d* jgl::Matrix3d::cpy(){
    return new jgl::Matrix3d(this);
}



jgl::Matrix3d* jgl::Matrix3d::set(double* values){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = values[x*3 + y];
        }
    }

    return this;
}
jgl::Matrix3d* jgl::Matrix3d::set(Matrix3d* mat3d){

    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = mat3d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix3d* jgl::Matrix3d::set(int x, int y, double value){
    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }else{
        this->matrix[x][y] = value;
    }

    return this;
}
jgl::Matrix3d* jgl::Matrix3d::setAll(double value){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = value;
        }
    }

    return this;
}



double jgl::Matrix3d::get(int x, int y){

    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }else{
        return this->matrix[x][y];
    }
}



std::string* jgl::Matrix3d::toString(){
    return new std::string(
        std::to_string(this->matrix[0][0]) + "," + std::to_string(this->matrix[0][1]) + "," + std::to_string(this->matrix[0][2]) + ";" + 
        std::to_string(this->matrix[1][0]) + "," + std::to_string(this->matrix[1][1]) + "," + std::to_string(this->matrix[1][2]) + ";" + 
        std::to_string(this->matrix[2][0]) + "," + std::to_string(this->matrix[2][1]) + "," + std::to_string(this->matrix[2][2]) + ";" 
    );
}



jgl::Matrix3d* jgl::Matrix3d::addAll(double value){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] += value;
        }
    }

    return this;
}
jgl::Matrix3d* jgl::Matrix3d::add(Matrix3d* mat3d){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] += mat3d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix3d* jgl::Matrix3d::add(int x, int y, double value){

    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }

    this->matrix[x][y] += value;

    return this;
}



jgl::Matrix3d* jgl::Matrix3d::mulAll(double value){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] *= value;
        }
    }

    return this;
}
jgl::Matrix3d* jgl::Matrix3d::mul(Matrix3d* mat3d){

    this->set( new jgl::Matrix3d(
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
jgl::Matrix3d* jgl::Matrix3d::mul(int x, int y, double value){

    if(x < 0 || x > 2 || y < 0 || y > 2){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }

    this->matrix[x][y] = this->matrix[x][y] * value;

    return this;
}



double jgl::Matrix3d::det(){

    return
        matrix[0][0]*matrix[1][1]*matrix[2][2] + 
        matrix[0][1]*matrix[1][2]*matrix[2][0] +
        matrix[0][2]*matrix[1][0]*matrix[2][1] -

        matrix[0][2]*matrix[1][1]*matrix[2][0] - 
        matrix[0][1]*matrix[1][0]*matrix[2][2] -
        matrix[0][0]*matrix[1][2]*matrix[2][1];
}



jgl::Matrix3d* jgl::Matrix3d::idt(){
    this->set(new Matrix3d());
    this->set(0, 0, 1);
    this->set(1, 1, 1);
    this->set(2, 2, 1);
    return this;
}



jgl::Matrix3d* jgl::Matrix3d::inv(){
        if(this->det() != 0){
        double tmp;
        jgl::Matrix3d* idt = (new jgl::Matrix3d())->idt();

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



jgl::Matrix3d* jgl::Matrix3d::rotate(double radians){
    return this->mul(new jgl::Matrix3d(radians));
}
jgl::Matrix3d* jgl::Matrix3d::setToRotation(double radians){
    return this->set(new jgl::Matrix3d(radians));
}
double jgl::Matrix3d::getRotation(){

    double scalingFactor = this->getScale();

    if(asin(this->matrix[0][1]*(1/scalingFactor)) < 0){
        return M_PI*2 - acos(this->matrix[0][0]);
    }else{
        return acos(this->matrix[0][0]*(1/scalingFactor));
    }
}



jgl::Matrix3d* jgl::Matrix3d::scale(double x, double y){
    return this->mul(new jgl::Matrix3d(x, 0, 0, 0, y, 0, 0, 0, 1));
}
jgl::Matrix3d* jgl::Matrix3d::scale(jgl::Vector2d* vec2d){
    return this->scale(vec2d->getX(), vec2d->getY());
}
double jgl::Matrix3d::getScale(){
    return sqrt(pow(this->matrix[0][0],2) + pow(this->matrix[0][1],2));
}
jgl::Matrix3d* jgl::Matrix3d::setToScaling(double x, double y){
    return this->set(new jgl::Matrix3d(x, 0, 0, 0, y, 0, 0, 0, 1));
}
jgl::Matrix3d* jgl::Matrix3d::setToScaling(jgl::Vector2d* vec2d){
    return this->setToScaling(vec2d->getX(), vec2d->getY());
}



jgl::Matrix3d* jgl::Matrix3d::translate(double x, double y){
    return this->mul(new jgl::Matrix3d(1, 0, x, 0, 1, y, 0, 0, 1));
}
jgl::Matrix3d* jgl::Matrix3d::translate(jgl::Vector2d* vec2d){
    return this->translate(vec2d->getX(), vec2d->getY());
}
jgl::Vector2d* jgl::Matrix3d::getTranslation(){
    return new jgl::Vector2d(this->matrix[0][2], this->matrix[1][2]);
}
jgl::Matrix3d* jgl::Matrix3d::setToTranslation(double x, double y){
    return this->set(new jgl::Matrix3d(1, 0, x, 0, 1, y, 0, 0, 1));
}
jgl::Matrix3d* jgl::Matrix3d::setToTranslation(jgl::Vector2d* vec2d){
    return this->setToTranslation(vec2d->getX(), vec2d->getY());
}


/**
 * Here private methods for computing matrix
 * Check private area in header file for more info
 */ 


void jgl::Matrix3d::setIdentityMatrix(jgl::Matrix3d* &idt, int x){

    double tmp;
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

void jgl::Matrix3d::substractRow(jgl::Matrix3d* &idt, int x, int y, int row){

    double tmp;
    //Check if it is already 0
    if( (tmp = this->matrix[x][y]) != 0 ){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] -= tmp*this->matrix[row][y];
            idt->matrix[x][y] -= tmp*idt->matrix[row][y];
        }
    }
}