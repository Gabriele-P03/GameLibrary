#ifndef Vector3F_H
#define Vector3F_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../matrix/mat4/Matrix4d.h"

namespace jgl{


    class Vector3f
    {
        private:
            float x, y, z;

        public:   

            Vector3f();
            Vector3f(float x, float y, float z);
            Vector3f(Vector3f* vec3f);
            Vector3f(std::string* fromString);
            
            float getX();
            float getY();
            float getZ();

            Vector3f* setX(float x);
            Vector3f* setY(float y);
            Vector3f* setZ(float z);
            Vector3f* set(Vector3f* vec3f);
            Vector3f* setAll(float x, float y, float z);

            Vector3f* addX(float x);
            Vector3f* addY(float y);
            Vector3f* addZ(float z);
            Vector3f* add(Vector3f* vec3f);
            Vector3f* addAll(float x, float y, float z);

            Vector3f* mulX(float x);
            Vector3f* mulY(float y);
            Vector3f* mulZ(float z);
            Vector3f* mul(Vector3f* vec3f);
            Vector3f* mulAll(float x, float y, float z);

            Vector3f* cpy();
    
            //Versor of the vector
            jgl::Vector3f* vrs();

            //Return lenght (module/norm) of the vector
            double lenght();

            //Return the distance from the given vector
            double dst(jgl::Vector3f* vec3f);


            //Return dot product
            double dot(jgl::Vector3f* vec3f);

            //Return the cross product
            jgl::Vector3f* crs(jgl::Vector3f* vec3f);

            //Return the angle between two vector in radiants
            double angleRad(jgl::Vector3f* vec3f);
            //Return the angle between two vector in grades
            double angleGrd(jgl::Vector3f* vec3f);


            //Return if the vector is null (lenght = 0)
            bool isNull();

            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector3f* vec3f);

            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector3f* vec3f);

            //Return if the vectors are parallel
            bool isParallel(jgl::Vector3f* vec3f);


            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector3f* vec3f);

            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector3f* vec3f);

            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector3f* vec3f);

            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector3f* vec3f);

            //Rotate vector taking as pivot (0, 0, 0), counter-clockwise
            Vector3f* rotate(double _rad, jgl::Vector3f* axis);

            //Rotate vector around pofloat by vec3f
            Vector3f* rotateAround(jgl::Vector3f* vec3f, double _rad, jgl::Vector3f* axis);

            //Return the vector as string (x, y, z)
            std::string* toString();



            static Vector3f xAxis;
            static Vector3f yAxis;
            static Vector3f zAxis;
    };  
}

#endif