#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "../../matrix/mat4/Matrix4d.h"
#include "../v3/Vector3d.h"

namespace jgl{

    class Vector3d;
    class Matrix4d;

    class Quaternion{

        private:
            double x, y, z, w;
        
        public:
            Quaternion();
            Quaternion(double x, double y, double z, double w);
            Quaternion(Quaternion* quaternion);
            Quaternion(jgl::Vector3d* vec3d);
            Quaternion(jgl::Matrix4d* mat);

            jgl::Quaternion* add(double x, double y, double z, double w);
            jgl::Quaternion* add(Quaternion* quaternion);

            jgl::Quaternion* mul(double x, double y, double z, double w);
            jgl::Quaternion* mul(Quaternion* quaternion);

            jgl::Quaternion* set(double x, double y, double z, double w);
            jgl::Quaternion* set(Quaternion* quaternion);

            jgl::Quaternion* conjugate();
            jgl::Quaternion* cpy();

            double dot(Quaternion* q);

            //Set this quaternion as identity one
            jgl::Quaternion* idt();

            //Return the lenght of the quaternion
            double nor();

            //Return the angle this quaternion represents 
            double getAngle();

            //Return the angle this quaternion represents around the given axis
            //double getAngleAround(jgl::Vector3d* vec3d);

            //Return the eular angle, which is the rotation around X-axis 
            double getPitch();
            //return the eular angle, which is the rotation around Z-axis
            double getRoll();
            //return the eular angle, which is the rotation around Y-axis
            double getYaw();
    };
}

#endif