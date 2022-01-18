#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "../../matrix/mat4/Matrix4.h"
#include "../v3/Vector3f.h"

namespace jgl{

    class Vector3f;
    class Matrix4;

    class Quaternion{

        public:
            float x, y, z, w;
        
            //Create a new quaternion as 0,0,0,0
            Quaternion();
            //Create a new quaternion as x,y,z,w
            Quaternion(float x, float y, float z, float w);
            //Create a new quaternion as the given one
            Quaternion(Quaternion* quaternion);
            //Create a new quaternion by the given axis unit-vector and angle in radians
            Quaternion(jgl::Vector3f* axis, float _rad);
            //Create a new quaternion by the given euler angles
            Quaternion(float yaw, float pitch, float roll);
            //Create a new quaternion by the given rotation matrix
            Quaternion(Matrix4* Matrix4);
            //Create a new quaternion by the given direction vector, passing before from matrix constructor with a vector
            Quaternion(Vector3f* vec3d);
            //Create a new quaternion by the given string as x,y,z,w
            Quaternion(std::string* fromString);



            Quaternion* add(float x, float y, float z, float w);
            Quaternion* add(Quaternion* quaternion);

            Quaternion* mul(float x, float y, float z, float w);
            Quaternion* mul(Quaternion* quaternion);

            Quaternion* set(float x, float y, float z, float w);
            Quaternion* set(Quaternion* quaternion);

            Quaternion* conjugate();
            Quaternion* cpy();

            float dot(Quaternion* q);

            //Set this quaternion as identity one
            jgl::Quaternion* idt();

            //Return the lenght of the quaternion
            float nor();

            //Return the angle this quaternion represents 
            float getAngle();
            
            float getPitch();
            float getYaw();
            float getRoll();

            float getX();
            float getY();
            float getZ();
            float getW();

            /**
             * @return the direction vector represented by this quaternion
             */ 
            Vector3f* getDirectionVector();
    };
}

#endif