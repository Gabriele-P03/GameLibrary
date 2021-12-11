#include "Matrix4d.h"

jgl::Matrix4d::Matrix4d(double x1y1, double x1y2, double x1y3, double x1y4, double x2y1, double x2y2, double x2y3, double x2y4, double x3y1, double x3y2, double x3y3, double x3y4, double x4y1, double x4y2, double x4y3, double x4y4){
    this->matrix[0][0] = x1y1; this->matrix[0][1] = x1y2; this->matrix[0][2] = x1y3; this->matrix[0][3] = x1y4;
    this->matrix[1][0] = x2y1; this->matrix[1][1] = x2y2; this->matrix[1][2] = x2y3; this->matrix[1][3] = x2y4;
    this->matrix[2][0] = x3y1; this->matrix[2][1] = x3y2; this->matrix[2][2] = x3y3; this->matrix[2][3] = x3y4;
    this->matrix[3][0] = x4y1; this->matrix[3][1] = x4y2; this->matrix[3][2] = x4y3; this->matrix[3][3] = x4y4;
}
jgl::Matrix4d::Matrix4d() : jgl::Matrix4d(0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0){}
jgl::Matrix4d::Matrix4d(jgl::Matrix4d* mat4d) : jgl::Matrix4d(
        mat4d->matrix[0][0], mat4d->matrix[0][1], mat4d->matrix[0][2], mat4d->matrix[0][3],
        mat4d->matrix[1][0], mat4d->matrix[1][1], mat4d->matrix[1][2], mat4d->matrix[1][3],
        mat4d->matrix[2][0], mat4d->matrix[2][1], mat4d->matrix[2][2], mat4d->matrix[2][3],
        mat4d->matrix[3][0], mat4d->matrix[3][1], mat4d->matrix[3][2], mat4d->matrix[3][3] 
    ){
}
jgl::Matrix4d::Matrix4d(jgl::Vector3d* position, jgl::Quaternion* rotation, jgl::Vector3d* scale){
    
}
jgl::Matrix4d::Matrix4d(jgl::Quaternion* rotation) : jgl::Matrix4d(new jgl::Vector3d(), rotation, new jgl::Vector3d()){}



jgl::Matrix4d* jgl::Matrix4d::cpy(){return new jgl::Matrix4d(this);}



jgl::Matrix4d* jgl::Matrix4d::idt(){return this->set(new double[16]{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1});}



jgl::Matrix4d* jgl::Matrix4d::set(double* values){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = values[x*4 + y];
        }
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::set(int x, int y, double value){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }else{
        this->matrix[x][y] = value;
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::set(jgl::Matrix4d* mat4d){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = mat4d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::setAll(double value){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = value;
        }
    }

    return this;
}



double jgl::Matrix4d::get(int x, int y){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }else{
        return this->matrix[x][y];
    }
}



jgl::Matrix4d* jgl::Matrix4d::mul(jgl::Matrix4d* mat4d){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] *= mat4d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::mulAll(double value){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] *= value;
        }
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::mul(int x, int y, double value){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }else{
        this->matrix[x][y] *= value;
        return this;
    }
}



jgl::Matrix4d* jgl::Matrix4d::add(jgl::Matrix4d* mat4d){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] += mat4d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::addAll(double value){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] += value;
        }
    }

    return this;
}
jgl::Matrix4d* jgl::Matrix4d::add(int x, int y, double value){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3D index error...";
        exit(-1);
    }else{
        this->matrix[x][y] += value;
        return this;
    }
}



double jgl::Matrix4d::det(){
    return
        matrix[0][0]*matrix[1][1]*matrix[2][2]*matrix[3][3] + 
        matrix[0][1]*matrix[1][2]*matrix[2][3]*matrix[3][0] +
        matrix[0][2]*matrix[1][3]*matrix[2][0]*matrix[3][1] +
        matrix[0][3]*matrix[1][0]*matrix[2][1]*matrix[3][2] -

        matrix[0][3]*matrix[1][2]*matrix[2][1]*matrix[3][0] - 
        matrix[1][3]*matrix[2][2]*matrix[3][1]*matrix[0][0] -
        matrix[2][3]*matrix[3][2]*matrix[0][1]*matrix[1][0] -
        matrix[3][3]*matrix[0][2]*matrix[1][1]*matrix[2][0];
}



jgl::Matrix4d* jgl::Matrix4d::setToRotation(jgl::Vector3d* direction, jgl::Vector3d* up){

    jgl::Vector3d* right = up->crs(direction);
    jgl::Vector3d* newUp = direction->crs(right);

    this->matrix[0][0] = right->getX();
    this->matrix[0][1] = newUp->getX();
    this->matrix[0][2] = direction->getX();

    this->matrix[1][0] = right->getY();
    this->matrix[1][1] = newUp->getY();
    this->matrix[1][2] = direction->getY();

    this->matrix[2][0] = right->getZ();
    this->matrix[2][1] = newUp->getZ();
    this->matrix[2][2] = direction->getZ();

    for(int i = 0; i < 4; i++){
        this->matrix[3][i] = 0;
        this->matrix[i][3] = 0;
    }

    this->matrix[3][3] = 1;

    return this;
}



jgl::Quaternion* jgl::Matrix4d::getQuaternion(){
    
    double qw = sqrt(1+this->matrix[0][0]+this->matrix[1][1]+this->matrix[2][2])/2;
    return new jgl::Quaternion(
        (this->matrix[2][1]-this->matrix[1][2])/(4*qw),
        (this->matrix[0][2]-this->matrix[2][0])/(4*qw),
        (this->matrix[1][0]-this->matrix[0][1])/(4*qw),
        qw
    );
}



jgl::Matrix4d* jgl::Matrix4d::inv(){

    if(this->det() != 0){
        double tmp;
        jgl::Matrix4d* idt = (new jgl::Matrix4d())->idt();

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

        //x3y0 nullify
        this->substractRow(idt, 3, 0, 0);
        //x3y1 nullify
        this->substractRow(idt, 3, 1, 1);
        //x3y2 nullify
        this->substractRow(idt, 3, 2, 2);
        //x3y3 as 1
        this->setIdentityMatrix(idt, 3);


        /**
         * Let's manupulate top-right stair
         */

        //x2y3 nullify
        this->substractRow(idt, 2, 3, 3);

        //x1y3 nullify 
        this->substractRow(idt, 1, 3, 3);
        //x1y2 nullify
        this->substractRow(idt, 1, 2, 2);

        //x0y3 nullify
        this->substractRow(idt, 0, 3, 3);
        //x0y2 nullify
        this->substractRow(idt, 0, 2, 2);
        //x0y1 nullify
        this->substractRow(idt, 0, 1, 1);

        return idt;
    }

    return nullptr;
}




/**
 * Here private methods for computing matrix
 * Check private area in header file for more info
 */ 


void jgl::Matrix4d::setIdentityMatrix(jgl::Matrix4d* &idt, int x){

    double tmp;
    /*
        Check if x,x is already 1. If it is 0, row will be swapped with the next one if the next one is not the third
    */
    if( (tmp = this->matrix[x][x]) != 0 && tmp != 1){
        tmp = this->matrix[x][x];
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] /= tmp;
            idt->matrix[x][y] /= tmp;
        }
    }else if(tmp == 0){
        //Swap
        for(int y = 0; y < 4; y++){
            tmp = this->matrix[x][y];
            this->matrix[x][y] = this->matrix[x+1][y];
            this->matrix[x+1][y] = tmp;

            tmp = idt->matrix[x][y];
            idt->matrix[x][y] = idt->matrix[x+1][y];
            idt->matrix[x+1][y] = tmp;
        }
    }
}

void jgl::Matrix4d::substractRow(jgl::Matrix4d* &idt, int x, int y, int row){

    double tmp;
    //Check if it is already 0
    if( (tmp = this->matrix[x][y]) != 0 ){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] -= tmp*this->matrix[row][y];
            idt->matrix[x][y] -= tmp*idt->matrix[row][y];
        }
    }
}