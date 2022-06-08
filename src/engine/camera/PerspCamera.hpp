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
#include "../input/mouse/MouseInput.h"

namespace jpl{

    class PerspCamera : public BaseCamera{

        private:

            float lastXMousePos, lastYMousePos;

        public:

            PerspCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far);

            virtual void updateFrustum() override;

            /**
             * Translate this camera by the given vector
             * @param translatingVector
             */ 
            virtual void translate(jgl::Vector3f* translatingVector);
            /**
             * Set to translation this camera by the given vector
             * @param translatingVector
             */ 
            virtual void setToTranslation(jgl::Vector3f* translatingVector);


            /**
             * Set direction vector of this camera
             * @param quaternion
             */ 
            virtual void setToRotation(jgl::Quaternion* quaternion);
            /**
             * Rotate this camera by the given rotation matrix
             * @param rotationMatrix
             */ 
            virtual void rotate(jgl::Matrix4* rotationMatrix);
            /**
             * Rotate this camera by the given rotation matrix
             * @param quaternion
             */ 
            virtual void rotate(jgl::Quaternion* quaternion);
            /**
             * Rotate this camera around the given point
             * @param point
             * @param rotationMatrix
             */ 
            virtual void rotateAround(jgl::Vector3f* point, jgl::Matrix4* rotationMatrix);


            /**
             * Transform the position, direction and up vector by the given transformation matrix
             * @param transformationMatrix
             */ 
            virtual void transform(jgl::Matrix4* transformationMatrix);

            /**
             * Project the given screen coordinates to 3D world game
             * @return world coords
             */ 
            jgl::Vector3f* project(jgl::Vector3f* screenCoords);

                        /**
             * Project the given screen coordinates to 3D world game
             * @return world coords
             */ 
            jgl::Vector3f* unproject(jgl::Vector3f* worldCoords);


            /**
             * Called in order to move camera as WASD movements
             * 
             * As this is a perspective camera it will also provides rotating system 
             *
             * @param speedMove speed which camera is moved at
             * @param speedRot speed which camera is rotated at
             * @param yawLock if yaw cannot do a full circula movement
             * @warning this method does NOT call update()
             * @warning in video-game zAxis and yAxis are inverted 
             */
            virtual void tick(float speedMove, float speedRot, bool yawLock);
    };
}

#endif