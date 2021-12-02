#ifndef Vector3d_H
#define Vector3d_H

#include <iostream>
#include <string>
#include "../../JMath.h"

namespace jgl{

    class Vector3d
    {
        private:
            double x, y, z;

        public:   

            Vector3d();
            Vector3d(double x, double y, double z);
            Vector3d(Vector3d* vec3d);
            Vector3d(std::string* fromString);
            
            double getX();
            double getY();
            double getZ();

            void setX(double x);
            void setY(double y);
            void setZ(double z);
            void set(Vector3d* vec3d);
            void setAll(double x, double y, double z);

            void addX(double x);
            void addY(double y);
            void addZ(double z);
            void add(Vector3d* vec3d);
            void addAll(double x, double y, double z);

            void mulX(double x);
            void mulY(double y);
            void mulZ(double z);
            void mul(Vector3d* vec3d);
            void mulAll(double x, double y, double z);

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
            void rotate(double _rad, jgl::Vector3d* axis);

            //Rotate vector around podouble by vec3d
            void rotateAround(jgl::Vector3d* vec3d, double _rad, jgl::Vector3d* axis);

            //Return the vector as string (x, y, z)
            std::string* toString();

             static jgl::Vector3d xAxis;
             static jgl::Vector3d yAxis;
             static jgl::Vector3d zAxis;
    };  
}



#endif