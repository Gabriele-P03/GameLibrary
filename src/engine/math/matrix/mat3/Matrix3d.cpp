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

    //The inverse matrix is available only if det is not 0
    if(this->det() != 0){
        jgl::Matrix3d* idt = new jgl::Matrix3d();
        idt->idt();

        double tmp;

        //Be sure that x0y0 is not 0
        if(this->matrix[0][0] != 0){
            tmp = 1/this->matrix[0][0];
            for(int y = 0; y < 3; y++){
                this->matrix[0][y] *= tmp;
                idt->matrix[0][y] *= tmp;
            } 
        }else{
            //x0y0 is 0, then first and second row must be swapped
            for(int y = 0; y < 3; y++){
                tmp = this->matrix[0][y];
                this->matrix[0][y] = this->matrix[1][y];
                this->matrix[1][y] = tmp;

                tmp = idt->matrix[0][y];
                idt->matrix[0][y] = idt->matrix[1][y];
                idt->matrix[1][y] = tmp;
            } 
        }

        //Nullify x1y0
        if(this->matrix[1][0] != 0){
            tmp = this->matrix[1][0] ;
            for(int y = 0; y < 3; y++){
                this->matrix[1][y] -= tmp*this->matrix[0][y];
                idt->matrix[1][y] -= tmp*idt->matrix[0][y];
            }
        }

        //Nullify x2y0
        if(this->matrix[2][0] != 0){
            tmp = this->matrix[2][0] ;
            for(int y = 0; y < 3; y++){
                this->matrix[2][y] -= tmp*this->matrix[0][y];
                idt->matrix[2][y] -= tmp*idt->matrix[0][y];
            }
        }

        //Null x2y1, but before be sure that x1y1 is 1
        if(this->matrix[1][1] != 1){
            tmp = 1/this->matrix[1][1];
            for(int y = 0; y < 3; y++){
                this->matrix[1][y] *= tmp;
                idt->matrix[1][y] *= tmp;
            }
        }
        if(this->matrix[2][1] != 0){
            tmp = this->matrix[2][1];
            for(int y = 0; y < 3; y++){
                this->matrix[2][y] -= tmp*this->matrix[1][y];
                idt->matrix[2][y] -= tmp*idt->matrix[1][y];
            }
        }

        //Be sure that x2y2 is 1
        if(this->matrix[2][2] != 1){
            tmp = 1/this->matrix[2][2];
            for(int y = 0; y < 3; y++){
                this->matrix[2][y] *= tmp;
                idt->matrix[2][y] *= tmp;
            }
        }

        //Now, let's nullify top-right corner
        //Begin from x1y2
        if(this->matrix[1][2] != 0){
            tmp = this->matrix[1][2];
            for(int y = 0; y < 3; y++){
                this->matrix[1][y] -= tmp*this->matrix[2][y];
                idt->matrix[1][y] -= tmp*idt->matrix[2][y];
            }
        }

        //Nullify x0y2
        if(this->matrix[0][2] != 0){
            tmp = this->matrix[0][2];
            for(int y = 0; y < 3; y++){
                this->matrix[0][y] -= tmp*this->matrix[2][y];
                idt->matrix[0][y] -= tmp*idt->matrix[2][y];
            }
        }

        //Nullify x0y1
        if(this->matrix[0][1] != 0){
            tmp = this->matrix[0][1];
            for(int y = 0; y < 3; y++){
                this->matrix[0][y] -= tmp*this->matrix[1][y];
                idt->matrix[0][y] -= tmp*idt->matrix[1][y];
            }
        }

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
    
    if(asin(this->matrix[0][1]) < 0){
        return M_PI*2 - acos(this->matrix[0][0]);
    }else{
        return acos(this->matrix[0][0]);
    }
}



jgl::Matrix3d* jgl::Matrix3d::scale(double x, double y){
    return this->mul(new jgl::Matrix3d(x, 0, 0, 0, y, 0, 0, 0, 1));
}
jgl::Matrix3d* jgl::Matrix3d::scale(jgl::Vector2d* vec2d){
    return this->scale(vec2d->getX(), vec2d->getY());
}
jgl::Vector2d* jgl::Matrix3d::getScale(){
    return new jgl::Vector2d(this->matrix[0][0], this->matrix[1][1]);
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