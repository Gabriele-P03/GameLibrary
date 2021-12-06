#ifndef VECTOR3I_H
#define VECTOR3I_H

#include <iostream>
#include <string>
#include "../../JMath.h"

namespace jgl{


    class Vector3i
    {
        private:
            int x, y, z;

        public:   

            Vector3i();
            Vector3i(int x, int y, int z);
            Vector3i(Vector3i* vec3i);
            Vector3i(std::string* fromString);
            
            int getX();
            int getY();
            int getZ();

            Vector3i* setX(int x);
            Vector3i* setY(int y);
            Vector3i* setZ(int z);
            Vector3i* set(Vector3i* vec3i);
            Vector3i* setAll(int x, int y, int z);

            Vector3i* addX(int x);
            Vector3i* addY(int y);
            Vector3i* addZ(int z);
            Vector3i* add(Vector3i* vec3i);
            Vector3i* addAll(int x, int y, int z);

            Vector3i* mulX(int x);
            Vector3i* mulY(int y);
            Vector3i* mulZ(int z);
            Vector3i* mul(Vector3i* vec3i);
            Vector3i* mulAll(int x, int y, int z);

            Vector3i* cpy();
    
            //Versor of the vector
            jgl::Vector3i* vrs();

            //Return lenght (module/norm) of the vector
            double lenght();

            //Return the distance from the given vector
            double dst(jgl::Vector3i* vec3i);


            //Return dot product
            double dot(jgl::Vector3i* vec3i);

            //Return the cross product
            jgl::Vector3i* crs(jgl::Vector3i* vec3i);

            //Return the angle between two vector in radiants
            double angleRad(jgl::Vector3i* vec3i);
            //Return the angle between two vector in grades
            double angleGrd(jgl::Vector3i* vec3i);


            //Return if the vector is null (lenght = 0)
            bool isNull();

            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector3i* vec3i);

            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector3i* vec3i);

            //Return if the vectors are parallel
            bool isParallel(jgl::Vector3i* vec3i);


            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector3i* vec3i);

            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector3i* vec3i);

            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector3i* vec3i);

            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector3i* vec3i);

            //Rotate vector taking as pivot (0, 0, 0), counter-clockwise
            Vector3i* rotate(double _rad, jgl::Vector3i* axis);

            //Rotate vector around point by vec3i
            Vector3i* rotateAround(jgl::Vector3i* vec3i, double _rad, jgl::Vector3i* axis);

            //Return the vector as string (x, y, z)
            std::string* toString();

             static Vector3i xAxis;
             static Vector3i yAxis;
             static Vector3i zAxis;
    };  
}

#endif