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


jgl::Matrix4d* jgl::Matrix4d::inv(){

        jgl::Matrix4d* idt = (new jgl::Matrix4d())->idt();

        //Substract the first row from the second
        for(int y = 0; y < 4; y++){
            this->matrix[1][y] -= this->matrix[0][y];
            idt->matrix[1][y] -= idt->matrix[0][y];
        }

        //Substract the first row from the third
        for(int y = 0; y < 4; y++){
            this->matrix[2][y] -= this->matrix[0][y];
            idt->matrix[2][y] -= idt->matrix[0][y];
        }

        //Add the first row to the fourth
        for(int y = 0; y < 4; y++){
            this->matrix[3][y] += this->matrix[0][y];
            idt->matrix[3][y] += idt->matrix[0][y];
        }

        //Switch the second row and the fourth
        double tmp;
        for(int y = 0; y < 4; y++){
            tmp = this->matrix[1][y];
            this->matrix[1][y] = this->matrix[3][y];
            this->matrix[3][y] = tmp;
            tmp = idt->matrix[1][y];
            idt->matrix[1][y] = idt->matrix[3][y];
            idt->matrix[3][y] = tmp;
        }

        //Multiply the second row by 1/2
        for(int y = 0; y < 4; y++){
            this->matrix[1][y] *= 0.5;
            idt->matrix[1][y] *= 0.5;
        }

        //Substract the second row from the first
        for(int y = 0; y < 4; y++){
            this->matrix[0][y] -= this->matrix[1][y];
            idt->matrix[0][y] -= idt->matrix[1][y];
        }

        //Add two times the second row to the third
        for(int y = 0; y < 4; y++){
            this->matrix[2][y] += 2*this->matrix[1][y];
            idt->matrix[2][y] += 2*idt->matrix[1][y];
        }

        //Multiply the third row by 1/2
        for(int y = 0; y < 4; y++){
            this->matrix[2][y] *= 0.5;
            idt->matrix[2][y] *= 0.5;
        }

        //Substract the third row from the second
        for(int y = 0; y < 4; y++){
            this->matrix[1][y] -= this->matrix[2][y];
            idt->matrix[1][y] -= idt->matrix[2][y];
        }

        //Add two times the third row to the fourth
        for(int y = 0; y < 4; y++){
            this->matrix[3][y] += 2*this->matrix[2][y];
            idt->matrix[3][y] += 2*idt->matrix[2][y];
        }

        //Multiply the third row by 1/4
        for(int y = 0; y < 4; y++){
            this->matrix[3][y] *= 0.25;
            idt->matrix[3][y] *= 0.25;
        }

        //Add the fourth row to the first
        for(int y = 0; y < 4; y++){
            this->matrix[0][y] += this->matrix[3][y];
            idt->matrix[0][y] += idt->matrix[3][y];
        }

        //Add the fourth row to the second
        for(int y = 0; y < 4; y++){
            this->matrix[1][y] += this->matrix[3][y];
            idt->matrix[1][y] += idt->matrix[3][y];
        }

        //Substract the fourth row from the third
        for(int y = 0; y < 4; y++){
            this->matrix[2][y] -= this->matrix[3][y];
            idt->matrix[2][y] -= idt->matrix[3][y];
        }
    
        return idt;
}