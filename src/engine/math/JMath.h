#ifndef JMATH_H
#define JMATH_H

#define _USE_MATH_DEFINES
#include <cmath>

#include <GLFW/glfw3.h>

//Return if the number is negative
bool isNegative(double x);

//Return if value is clamp bewteen min and max (both excluded)
bool isClamp(double x, double _min, double _max);

//Return hypotenuse which is form by the triangle with given cathetus
double hypotenus(double x1, double x2);

//Return the other cathetus which is form by the triangle
double cathetus(double hypotenus, double x1);

//Return the given radiant angle in degrees 
double toDegree(double _rad);

//Return the given degrees angle in radiants
double toRad(double _deg);

/**
 * @return given coordinates into range [-1; +1]
 */ 
float* jplOpenGlCoords(int x, int y);


#endif