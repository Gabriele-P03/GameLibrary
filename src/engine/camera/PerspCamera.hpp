/**
 * 
 * A perspective camera is a camera which can move on Z axis and rotate also around X and Y axis
 * Thus make a perspective once the right chose for a 3D game
 * 
 * @author Gabriele-P03
 */ 

#ifndef PERSPCAMERA_JPL_HPP
#define PERSPCAMERA_JPL_HPP

#include "BaseCamera.hpp"

namespace jpl{

    class PerspCamera : public BaseCamera{

        private:


        public:

            PerspCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far);

            void translate(float x, float y, float z);
            void translate(jgl::Vector3f* translatingVector);

            void rotate(float yaw, float pitch, float roll);
            void rotate(jgl::Quaternion* q);
            void rotate(jgl::Matrix4* mat);

            void setFOV(float FOV);
    };
}

#endif