#ifndef Vector3F_H
#define Vector3F_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../matrix/mat4/Matrix4.h"

namespace jgl{

    class Matrix4;
    class Quaternion;

    class Vector3f
    {
        private:
            float x, y, z;

        public:   

            Vector3f();
            Vector3f(float x, float y, float z);
            Vector3f(Vector3f* vec3d);
            Vector3f(Matrix4* mat4d);
            Vector3f(Quaternion* quaternion);
            Vector3f(std::string* fromString);
            
            float getX();
            float getY();
            float getZ();

            Vector3f* setX(float x);
            Vector3f* setY(float y);
            Vector3f* setZ(float z);
            Vector3f* set(Vector3f* vec3d);
            Vector3f* setAll(float x, float y, float z);

            Vector3f* addX(float x);
            Vector3f* addY(float y);
            Vector3f* addZ(float z);
            Vector3f* add(Vector3f* vec3d);
            Vector3f* addAll(float x, float y, float z);

            Vector3f* mulX(float x);
            Vector3f* mulY(float y);
            Vector3f* mulZ(float z);
            Vector3f* mul(Vector3f* vec3d);
            Vector3f* mulAll(float x, float y, float z);

            Vector3f* cpy();
    
            //Versor of the vector
            jgl::Vector3f* vrs();

            //Return lenght (module/norm) of the vector
            float lenght();

            //Return the distance from the given vector
            float dst(jgl::Vector3f* vec3d);


            //Return dot product
            float dot(jgl::Vector3f* vec3d);

            //Return the cross product
            jgl::Vector3f* crs(jgl::Vector3f* vec3d);

            //Return the angle between two vector in radiants
            float angleRad(jgl::Vector3f* vec3d);
            //Return the angle between two vector in grades
            float angleGrd(jgl::Vector3f* vec3d);


            //Return if the vector is null (lenght = 0)
            bool isNull();

            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector3f* vec3d);

            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector3f* vec3d);

            //Return if the vectors are parallel
            bool isParallel(jgl::Vector3f* vec3d);


            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector3f* vec3d);

            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector3f* vec3d);

            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector3f* vec3d);

            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector3f* vec3d);

            //Rotate vector taking as pivot (0, 0, 0), counter-clockwise
            Vector3f* rotate(float _rad, jgl::Vector3f* axis);

            //Rotate vector around pofloat by vec3d
            Vector3f* rotateAround(jgl::Vector3f* vec3d, float _rad, jgl::Vector3f* axis);

            //Return the vector as string (x, y, z)
            std::string* toString();



            //Get the rotation matrix of this direction vector. Call vrs() before
            Matrix4* getRotationMatrix();
            //Get the translation matrix of this position vector. Call vrs() before
            Matrix4* getTranslationMatrix();
            //Get the scaling matrix of this scale vector. Call vrs() before
            Matrix4* getScalingMatrix();



            static Vector3f xAxis;
            static Vector3f yAxis;
            static Vector3f zAxis;
    };  
}

#endif