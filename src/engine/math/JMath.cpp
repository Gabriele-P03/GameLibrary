#include "JMath.h"

bool isNegative(double x){
    return x < 0;
}

bool isClamp(double x, double _min, double _max){
    return x < _max && x > _min;
}

double hypotenus(double x1, double x2){
    return sqrt( pow(x1, 2) + pow(x2, 2));
}

double cathetus(double hypotenus, double x1){
    return sqrt( pow(hypotenus, 2) - pow(x1, 2));
}

double toDegree(double _rad){
    return _rad * (180 / M_PI);
}

double toRad(double _deg){
    return _deg * (M_PI / 180);
}

float* jplOpenGlCoords(int x, int y){
    int w, h;
    glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
    return new float[2]{
        ((float)x - (w/2)) / (w/2),
        ((float)y - (h/2)) / (h/2)
    };
}