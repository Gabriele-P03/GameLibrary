#include "Matrix3d.hpp"

jgl::Matrix3d::Matrix3d(double x1y1, double x1y2, double x1y3, double x2y1, double x2y2, double x2y3, double x3y1, double x3y2, double x3y3){
    this->matrix[0][0] = x1y1; this->matrix[0][1] = x1y2; this->matrix[0][2] = x1y3;
    this->matrix[1][0] = x2y1; this->matrix[1][1] = x2y2; this->matrix[1][2] = x2y3;
    this->matrix[2][0] = x3y1; this->matrix[2][1] = x3y2; this->matrix[2][2] = x3y3;
}

jgl::Matrix3d::Matrix3d(double** x1y1){
    this->set(x1y1);
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
        cos(yaw), -sin(yaw), 0,
        sin(yaw), cos(yaw), 0,
        0, 0, 1){

}

jgl::Matrix3d::Matrix3d() : jgl::Matrix3d::Matrix3d(0, 0, 0, 
                                                    0, 0, 0, 
                                                    0, 0, 0){
}

jgl::Matrix3d* jgl::Matrix3d::cpy(){
    return new jgl::Matrix3d(this);
}

jgl::Matrix3d* jgl::Matrix3d::set(double** mat3d){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            this->matrix[x][y] = mat3d[x][y];
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

        matrix[0][2]*matrix[1][1]*matrix[2][0] + 
        matrix[0][1]*matrix[1][0]*matrix[2][2] +
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

    //The inverse matrix is available only if det is not 0
    if(this->det() != 0){
        jgl::Matrix3d* idt = new jgl::Matrix3d();
        idt->idt();
        this->matrix[1][0] = 0;

        this->matrix[2][0] += -2*this->matrix[0][0];
        this->matrix[2][1] += -2*this->matrix[0][1];
        this->matrix[2][2] += -2*this->matrix[0][2];
        idt->matrix[2][0] += -2*idt->matrix[0][0];
        idt->matrix[2][1] += -2*idt->matrix[0][1];
        idt->matrix[2][2] += -2*idt->matrix[0][2];

        this->matrix[2][0] += 0.333333333*this->matrix[1][0];
        this->matrix[2][1] += 0.333333333*this->matrix[1][1];
        this->matrix[2][2] += 0.333333333*this->matrix[1][2];
        idt->matrix[2][0] += 0.333333333*idt->matrix[1][0];
        idt->matrix[2][1] += 0.333333333*idt->matrix[1][1];
        idt->matrix[2][2] += 0.333333333*idt->matrix[1][2];

        this->matrix[1][0] += -0.3*this->matrix[2][0];
        this->matrix[1][1] += -0.3*this->matrix[2][1];
        this->matrix[1][2] += -0.3*this->matrix[2][2];
        idt->matrix[1][0] += -0.3*idt->matrix[2][0];
        idt->matrix[1][1] += -0.3*idt->matrix[2][1];
        idt->matrix[1][2] += -0.3*idt->matrix[2][2];

        this->matrix[0][0] += 0.6*this->matrix[2][0];
        this->matrix[0][1] += 0.6*this->matrix[2][1];
        this->matrix[0][2] += 0.6*this->matrix[2][2];
        idt->matrix[0][0] += 0.6*idt->matrix[2][0];
        idt->matrix[0][1] += 0.6*idt->matrix[2][1];
        idt->matrix[0][2] += 0.6*idt->matrix[2][2];

        this->matrix[0][0] += -0.333333333*this->matrix[1][0];
        this->matrix[0][1] += -0.333333333*this->matrix[1][1];
        this->matrix[0][2] += -0.333333333*this->matrix[1][2];
        idt->matrix[0][0] += -0.333333333*idt->matrix[1][0];
        idt->matrix[0][1] += -0.333333333*idt->matrix[1][1];
        idt->matrix[0][2] += -0.333333333*idt->matrix[1][2];

        for(int x = 0; x < 3; x++){
            double k = 1/this->matrix[x][x];
            for(int y = 0; y < 3; y++){           
                this->mul(x, y, k);
                idt->mul(x, y, k);
            }
        }

        return idt;
    }

    return nullptr;
}

jgl::Matrix3d* jgl::Matrix3d::rotate(double radians){

    return this->mul(new jgl::Matrix3d(radians));
}