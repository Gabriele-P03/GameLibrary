#ifndef Vector3D_H
#define Vector3D_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../matrix/mat4/Matrix4d.h"

namespace jgl{

    class Matrix4d;
    class Quaternion;

    class Vector3d
    {
        private:
            double x, y, z;

        public:   

            Vector3d();
            Vector3d(double x, double y, double z);
            Vector3d(Vector3d* vec3d);
            Vector3d(Matrix4d* mat4d);
            Vector3d(Quaternion* quaternion);
            Vector3d(std::string* fromString);
            
            double getX();
            double getY();
            double getZ();

            Vector3d* setX(double x);
            Vector3d* setY(double y);
            Vector3d* setZ(double z);
            Vector3d* set(Vector3d* vec3d);
            Vector3d* setAll(double x, double y, double z);

            Vector3d* addX(double x);
            Vector3d* addY(double y);
            Vector3d* addZ(double z);
            Vector3d* add(Vector3d* vec3d);
            Vector3d* addAll(double x, double y, double z);

            Vector3d* mulX(double x);
            Vector3d* mulY(double y);
            Vector3d* mulZ(double z);
            Vector3d* mul(Vector3d* vec3d);
            Vector3d* mulAll(double x, double y, double z);

            Vector3d* cpy();
    
            //Versor of the vector
            jgl::Vector3d* vrs();

            //Return lenght (module/norm) of the vector
            double lenght();

            //Return the distance from the given vector
            double dst(jgl::Vector3d* vec3d);


            //Return dot product
            double dot(jgl::Vector3d* vec3d);

            //Return the cross product
            jgl::Vector3d* crs(jgl::Vector3d* vec3d);

            //Return the angle between two vector in radiants
            double angleRad(jgl::Vector3d* vec3d);
            //Return the angle between two vector in grades
            double angleGrd(jgl::Vector3d* vec3d);


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
            Vector3d* rotate(double _rad, jgl::Vector3d* axis);

            //Rotate vector around podouble by vec3d
            Vector3d* rotateAround(jgl::Vector3d* vec3d, double _rad, jgl::Vector3d* axis);

            //Return the vector as string (x, y, z)
            std::string* toString();



            //Get the rotation matrix of this direction vector. Call vrs() before
            Matrix4d* getRotationMatrix();
            //Get the translation matrix of this position vector. Call vrs() before
            Matrix4d* getTranslationMatrix();
            //Get the scaling matrix of this scale vector. Call vrs() before
            Matrix4d* getScalingMatrix();



            static Vector3d xAxis;
            static Vector3d yAxis;
            static Vector3d zAxis;
    };  
}

#endif