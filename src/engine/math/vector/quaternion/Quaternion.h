#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "../../matrix/mat4/Matrix4d.h"
#include "../v3/Vector3d.h"

namespace jgl{

    class Vector3d;
    class Matrix4d;

    class Quaternion{

        public:
            double x, y, z, w;
        
            //Create a new quaternion as 0,0,0,0
            Quaternion();
            //Create a new quaternion as x,y,z,w
            Quaternion(double x, double y, double z, double w);
            //Create a new quaternion as the given one
            Quaternion(Quaternion* quaternion);
            //Create a new quaternion by the given axis unit-vector and angle in radians
            Quaternion(jgl::Vector3d* axis, double _rad);
            //Create a new quaternion by the given euler angles
            Quaternion(double yaw, double pitch, double roll);
            //Create a new quaternion by the given rotation matrix
            Quaternion(Matrix4d* matrix4d);
            //Create a new quaternion by the given direction vector, passing before from matrix constructor with a vector
            Quaternion(Vector3d* vec3d);
            //Create a new quaternion by the given string as x,y,z,w
            Quaternion(std::string* fromString);



            Quaternion* add(double x, double y, double z, double w);
            Quaternion* add(Quaternion* quaternion);

            Quaternion* mul(double x, double y, double z, double w);
            Quaternion* mul(Quaternion* quaternion);

            Quaternion* set(double x, double y, double z, double w);
            Quaternion* set(Quaternion* quaternion);

            Quaternion* conjugate();
            Quaternion* cpy();

            double dot(Quaternion* q);

            //Set this quaternion as identity one
            jgl::Quaternion* idt();

            //Return the lenght of the quaternion
            double nor();

            //Return the angle this quaternion represents 
            double getAngle();
            
            double getPitch();
            double getYaw();
            double getRoll();

            double getX();
            double getY();
            double getZ();
            double getW();

            /**
             * @return the direction vector represented by this quaternion
             */ 
            Vector3d* getDirectionVector();
    };
}

#endif