#include "Matrix4.h"

jgl::Matrix4::Matrix4(float x1y1, float x1y2, float x1y3, float x1y4, float x2y1, float x2y2, float x2y3, float x2y4, float x3y1, float x3y2, float x3y3, float x3y4, float x4y1, float x4y2, float x4y3, float x4y4){
    this->matrix[0][0] = x1y1; this->matrix[0][1] = x1y2; this->matrix[0][2] = x1y3; this->matrix[0][3] = x1y4;
    this->matrix[1][0] = x2y1; this->matrix[1][1] = x2y2; this->matrix[1][2] = x2y3; this->matrix[1][3] = x2y4;
    this->matrix[2][0] = x3y1; this->matrix[2][1] = x3y2; this->matrix[2][2] = x3y3; this->matrix[2][3] = x3y4;
    this->matrix[3][0] = x4y1; this->matrix[3][1] = x4y2; this->matrix[3][2] = x4y3; this->matrix[3][3] = x4y4;
}
jgl::Matrix4::Matrix4() : jgl::Matrix4(0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0){}
jgl::Matrix4::Matrix4(jgl::Matrix4* mat4d) : jgl::Matrix4(
        mat4d->matrix[0][0], mat4d->matrix[0][1], mat4d->matrix[0][2], mat4d->matrix[0][3],
        mat4d->matrix[1][0], mat4d->matrix[1][1], mat4d->matrix[1][2], mat4d->matrix[1][3],
        mat4d->matrix[2][0], mat4d->matrix[2][1], mat4d->matrix[2][2], mat4d->matrix[2][3],
        mat4d->matrix[3][0], mat4d->matrix[3][1], mat4d->matrix[3][2], mat4d->matrix[3][3] 
    ){
}
jgl::Matrix4::Matrix4(jgl::Vector3d* position, jgl::Quaternion* rotation, float scale){
    this->setToTranslation(position, true);
    this->scale(scale, scale, scale);
    this->rotate(rotation);
}
jgl::Matrix4::Matrix4(Vector3d* position, Quaternion* rotation) : jgl::Matrix4(position->cpy()->vrs(), rotation, position->lenght()){}
jgl::Matrix4::Matrix4(jgl::Quaternion* q){
    this->set(new float[16]{
        1-2*(float)pow(q->y, 2)-2*(float)pow(q->z, 2), 2*q->x*q->y - 2*q->z*q->w, 2*q->x*q->z + 2*q->y*q->w, 0,
        2*q->x*q->y + 2*q->z*q->w, 1-2*(float)pow(q->x, 2)-2*(float)pow(q->z, 2), 2*q->y*q->z - 2*q->x*q->w, 0,
        2*q->x*q->z - 2*q->y*q->w, 2*q->y*q->z + 2*q->x*q->w, 1-2*(float)pow(q->x, 2)-2*(float)pow(q->y, 2), 0,
        0, 0, 0, 1
    });
}
jgl::Matrix4::Matrix4(jgl::Vector3d* direction){
    this->setToRotation(direction, &jgl::Vector3d::yAxis, true);
}       
jgl::Matrix4::Matrix4(float yaw, float pitch, float roll){
    float sy = sin(yaw), cy = cos(yaw), sp = sin(pitch), cp = cos(pitch), sr = sin(roll), cr = cos(roll);

    this->set( new float[16]{  
                cp*cy, -cp*sy*cr+sp*sr, cp*sy*sr+sp*cr, 0,
                sy,     cy*cr,          -cy*sr, 0,
                -sp*cy, sp*sy*cr+cp*sr, -sp*sy*sr+cp*cr, 0,
                0,0,0,1
            }
    );
}
jgl::Matrix4::Matrix4(std::string* fromString){
    std::string cpy = std::string(*fromString);

    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = atoi(cpy.substr(0, cpy.find_first_of(',')).c_str());
        }
        cpy = cpy.substr(cpy.find_first_of(';'));
    }
}


jgl::Matrix4* jgl::Matrix4::cpy(){return new jgl::Matrix4(this);}



jgl::Matrix4* jgl::Matrix4::idt(){return this->set(new float[16]{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1});}



jgl::Matrix4* jgl::Matrix4::set(float* values){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = values[x*4 + y];
        }
    }

    return this;
}
jgl::Matrix4* jgl::Matrix4::set(int x, int y, float value){
    if(x < 0 || x > 3 || y < 0 || y > 3){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }else{
        this->matrix[x][y] = value;
    }

    return this;
}
jgl::Matrix4* jgl::Matrix4::set(jgl::Matrix4* mat4d){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = mat4d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix4* jgl::Matrix4::setAll(float value){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] = value;
        }
    }

    return this;
}



float jgl::Matrix4::get(int x, int y){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }else{
        return this->matrix[x][y];
    }
}



jgl::Matrix4* jgl::Matrix4::mul(jgl::Matrix4* mat4d){

    float count = 0;
    jgl::Matrix4* buffer = new jgl::Matrix4();
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            int pos = 0;
            buffer->matrix[x][y] = 
            this->matrix[x][pos]*mat4d->matrix[pos++][y] +
            this->matrix[x][pos]*mat4d->matrix[pos++][y] +
            this->matrix[x][pos]*mat4d->matrix[pos++][y] +
            this->matrix[x][pos]*mat4d->matrix[pos][y];
        }
    }

    return this->set(buffer);

}
jgl::Matrix4* jgl::Matrix4::mulAll(float value){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] *= value;
        }
    }

    return this;
}
jgl::Matrix4* jgl::Matrix4::mul(int x, int y, float value){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }else{
        this->matrix[x][y] *= value;
        return this;
    }
}



jgl::Matrix4* jgl::Matrix4::add(jgl::Matrix4* mat4d){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] += mat4d->matrix[x][y];
        }
    }

    return this;
}
jgl::Matrix4* jgl::Matrix4::addAll(float value){
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] += value;
        }
    }

    return this;
}
jgl::Matrix4* jgl::Matrix4::add(int x, int y, float value){
    if(x < 0 || x > 3 || y < 3 || y > 3){
        std::cout<<"JGL Matrix3 index error...";
        exit(-1);
    }else{
        this->matrix[x][y] += value;
        return this;
    }
}



float jgl::Matrix4::det(){
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


jgl::Matrix4* jgl::Matrix4::rotate(jgl::Quaternion* rotation){
    return this->mul(new jgl::Matrix4(rotation));
}
jgl::Matrix4* jgl::Matrix4::rotate(jgl::Vector3d* rotation){
    return this->mul(new jgl::Matrix4(rotation));
}
jgl::Matrix4* jgl::Matrix4::rotate(float yaw, float pitch, float roll){
    return this->mul(new jgl::Matrix4(yaw, pitch, roll));
}
jgl::Matrix4* jgl::Matrix4::setToRotation(jgl::Quaternion* rotation, bool idt){

    if(idt)
        this->idt();

    return this
    ->set(0, 0, (1-2*rotation->y*rotation->y - 2*rotation->z*rotation->z))
    ->set(0, 1, (2*rotation->x*rotation->y - 2*rotation->z*rotation->w))
    ->set(0, 2, (2*rotation->x*rotation->z + 2*rotation->w*rotation->y))

    ->set(1, 0, (2*rotation->x*rotation->y + 2*rotation->z*rotation->w))
    ->set(1, 1, (1-2*rotation->x*rotation->x - 2*rotation->z*rotation->z))
    ->set(1, 2, (2*rotation->y*rotation->z - 2*rotation->w*rotation->x))

    ->set(2, 0, (2*rotation->x*rotation->z - 2*rotation->w*rotation->y))
    ->set(2, 1, (2*rotation->y*rotation->z + 2*rotation->w*rotation->x))
    ->set(2, 2, (1-2*rotation->x*rotation->x - 2*rotation->y*rotation->y));
}
jgl::Matrix4* jgl::Matrix4::setToRotation(jgl::Vector3d* direction, jgl::Vector3d* up, bool idt){

    if(idt)
        this->idt();

    jgl::Vector3d* right = direction->crs(up);
    right->vrs();
    jgl::Vector3d* newUp = right->crs(direction);
    newUp->vrs();

    this->matrix[0][0] = right->getX(); 
    this->matrix[0][1] = newUp->getX(); 
    this->matrix[0][2] = direction->getX();
    this->matrix[0][3] = 0;
    
    this->matrix[1][0] = right->getY(); 
    this->matrix[1][1] = newUp->getY(); 
    this->matrix[1][2] = direction->getY();
    this->matrix[1][3] = 0;

    this->matrix[2][0] = right->getZ(); 
    this->matrix[2][1] = newUp->getZ(); 
    this->matrix[2][2] = direction->getZ();
    this->matrix[2][3] = 0;

    this->matrix[3][0] = 0; 
    this->matrix[3][1] = 0; 
    this->matrix[3][2] = 0;
    this->matrix[3][3] = 1;

    return this;
 }
jgl::Vector3d* jgl::Matrix4::getRotation(){
    return new jgl::Vector3d(this->matrix[0][2], this->matrix[1][2], this->matrix[2][2]);
}

jgl::Matrix4* jgl::Matrix4::translate(float x, float y, float z){
    return this->translate(new jgl::Vector3d(x, y, z));
}
jgl::Matrix4* jgl::Matrix4::translate(jgl::Vector3d* position){
    return this->mul( (new jgl::Matrix4())->setToTranslation(position, true) );
}
jgl::Matrix4* jgl::Matrix4::setToTranslation(float x, float y, float z, bool idt){    
    return this->setToTranslation(new jgl::Vector3d(x, y, z), idt);
}
jgl::Matrix4* jgl::Matrix4::setToTranslation(jgl::Vector3d* position, bool idt){
    if(idt)
        this->idt();
        
    return this->set(3, 0, position->getX())->set(3, 1, position->getY())->set(3, 2, position->getZ());
}
jgl::Vector3d* jgl::Matrix4::getTranslation(){
    return new jgl::Vector3d(this->matrix[0][2], this->matrix[1][2], this->matrix[2][2]);
}


jgl::Matrix4* jgl::Matrix4::scale(float x, float y, float z){
    return this->scale(new jgl::Vector3d(x, y, z));
}
jgl::Matrix4* jgl::Matrix4::scale(jgl::Vector3d* scale){
    return this->mul( (new jgl::Matrix4())->setToScale(scale, true) );
}
jgl::Matrix4* jgl::Matrix4::setToScale(float x, float y, float z, bool idt){
    return this->setToScale(new jgl::Vector3d(x, y, z), idt);
}
jgl::Matrix4* jgl::Matrix4::setToScale(jgl::Vector3d* scale, bool idt){

    if(idt)
        this->idt();

    return this->set(0, 0, scale->getX())->set(1, 1, scale->getY())->set(2, 2, scale->getZ());
}
jgl::Vector3d* jgl::Matrix4::getScale(){
    return new jgl::Vector3d(this->matrix[0][0], this->matrix[1][1], this->matrix[2][2]);
}



jgl::Quaternion* jgl::Matrix4::getQuaternion(){
    jgl::Quaternion q;
    float trace = this->matrix[0][0] + this->matrix[1][1] + this->matrix[2][2]; // I removed + 1.0f; see discussion with Ethan
    if( trace > 0 ) {
            float s = 0.5f / sqrtf(trace+ 1.0f);
            q.w = 0.25f / s;
            q.x = ( this->matrix[2][1] - this->matrix[1][2] ) * s;
            q.y = ( this->matrix[0][2] - this->matrix[2][0] ) * s;
            q.z = ( this->matrix[1][0] - this->matrix[0][1] ) * s;
    } else {
        if ( this->matrix[0][0] > this->matrix[1][1] && this->matrix[0][0] > this->matrix[2][2] ) {
            float s = 2.0f * sqrtf( 1.0f + this->matrix[0][0] - this->matrix[1][1] - this->matrix[2][2]);
            q.w = (this->matrix[2][1] - this->matrix[1][2] ) / s;
            q.x = 0.25f * s;
            q.y = (this->matrix[0][1] + this->matrix[1][0] ) / s;
            q.z = (this->matrix[0][2] + this->matrix[2][0] ) / s;
        } else if (this->matrix[1][1] > this->matrix[2][2]) {
        float s = 2.0f * sqrtf( 1.0f + this->matrix[1][1] - this->matrix[0][0] - this->matrix[2][2]);
            q.w = (this->matrix[0][2] - this->matrix[2][0] ) / s;
            q.x = (this->matrix[0][1] + this->matrix[1][0] ) / s;
            q.y = 0.25f * s;
            q.z = (this->matrix[1][2] + this->matrix[2][1] ) / s;
        } else {
            float s = 2.0f * sqrtf( 1.0f + this->matrix[2][2] - this->matrix[0][0] - this->matrix[1][1] );
            q.w = (this->matrix[1][0] - this->matrix[0][1] ) / s;
            q.x = (this->matrix[0][2] + this->matrix[2][0] ) / s;
            q.y = (this->matrix[1][2] + this->matrix[2][1] ) / s;
            q.z = 0.25f * s;
        }
    }

    return q.cpy();
}



jgl::Matrix4* jgl::Matrix4::inv(){

    if(this->det() != 0){
        float tmp;
        jgl::Matrix4* idt = (new jgl::Matrix4())->idt();

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


std::string* jgl::Matrix4::toString(){
    return new std::string(
        std::to_string(this->matrix[0][0]) + "," + std::to_string(this->matrix[0][1]) + "," + std::to_string(this->matrix[0][2]) + "," + std::to_string(this->matrix[0][3]) + ";" +
        std::to_string(this->matrix[1][0]) + "," + std::to_string(this->matrix[1][1]) + "," + std::to_string(this->matrix[1][2]) + "," + std::to_string(this->matrix[1][3]) + ";" +
        std::to_string(this->matrix[2][0]) + "," + std::to_string(this->matrix[2][1]) + "," + std::to_string(this->matrix[2][2]) + "," + std::to_string(this->matrix[2][3]) + ";" +
        std::to_string(this->matrix[3][0]) + "," + std::to_string(this->matrix[3][1]) + "," + std::to_string(this->matrix[3][2]) + "," + std::to_string(this->matrix[3][3])
    );
}



/**
 * Here private methods for computing matrix
 * Check private area in header file for more info
 */ 


void jgl::Matrix4::setIdentityMatrix(jgl::Matrix4* &idt, int x){

    float tmp;
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

void jgl::Matrix4::substractRow(jgl::Matrix4* &idt, int x, int y, int row){

    float tmp;
    //Check if it is already 0
    if( (tmp = this->matrix[x][y]) != 0 ){
        for(int y = 0; y < 4; y++){
            this->matrix[x][y] -= tmp*this->matrix[row][y];
            idt->matrix[x][y] -= tmp*idt->matrix[row][y];
        }
    }
}

jgl::Matrix4* jgl::Matrix4::matIdt = (new jgl::Matrix4())->idt();