#ifndef Vector3D_H
#define Vector3D_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../matrix/mat4/Matrix4.h"

namespace jgl{

    class Matrix4;
    class Quaternion;

    class Vector3d
    {
        private:
            float x, y, z;

        public:   

            Vector3d();
            Vector3d(float x, float y, float z);
            Vector3d(Vector3d* vec3d);
            Vector3d(Matrix4* mat4d);
            Vector3d(Quaternion* quaternion);
            Vector3d(std::string* fromString);
            
            float getX();
            float getY();
            float getZ();

            Vector3d* setX(float x);
            Vector3d* setY(float y);
            Vector3d* setZ(float z);
            Vector3d* set(Vector3d* vec3d);
            Vector3d* setAll(float x, float y, float z);

            Vector3d* addX(float x);
            Vector3d* addY(float y);
            Vector3d* addZ(float z);
            Vector3d* add(Vector3d* vec3d);
            Vector3d* addAll(float x, float y, float z);

            Vector3d* mulX(float x);
            Vector3d* mulY(float y);
            Vector3d* mulZ(float z);
            Vector3d* mul(Vector3d* vec3d);
            Vector3d* mulAll(float x, float y, float z);

            Vector3d* cpy();
    
            //Versor of the vector
            jgl::Vector3d* vrs();

            //Return lenght (module/norm) of the vector
            float lenght();

            //Return the distance from the given vector
            float dst(jgl::Vector3d* vec3d);


            //Return dot product
            float dot(jgl::Vector3d* vec3d);

            //Return the cross product
            jgl::Vector3d* crs(jgl::Vector3d* vec3d);

            //Return the angle between two vector in radiants
            float angleRad(jgl::Vector3d* vec3d);
            //Return the angle between two vector in grades
            float angleGrd(jgl::Vector3d* vec3d);


            //Return if the vector is null (lenght = 0)
            bool isNull();

            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector3d* vec3d);

            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector3d* vec3d);

            //Return if the vectors are parallel
            bool isParallel(jgl::Vector3d* vec3d);


            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector3d* vec3d);

            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector3d* vec3d);

            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector3d* vec3d);

            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector3d* vec3d);

            //Rotate vector taking as pivot (0, 0, 0), counter-clockwise
            Vector3d* rotate(float _rad, jgl::Vector3d* axis);

            //Rotate vector around pofloat by vec3d
            Vector3d* rotateAround(jgl::Vector3d* vec3d, float _rad, jgl::Vector3d* axis);

            //Return the vector as string (x, y, z)
            std::string* toString();



            //Get the rotation matrix of this direction vector. Call vrs() before
            Matrix4* getRotationMatrix();
            //Get the translation matrix of this position vector. Call vrs() before
            Matrix4* getTranslationMatrix();
            //Get the scaling matrix of this scale vector. Call vrs() before
            Matrix4* getScalingMatrix();



            static Vector3d xAxis;
            static Vector3d yAxis;
            static Vector3d zAxis;
    };  
}

#endif