/**
 * This is an abstraction of a camera for 2D/3D game.
 * 
 * Its position, direction and other information will be stored as it was in a 3D game,
 * even if you're developing a 2D one
 * 
 * @author Gabriele-P03
 */ 

#ifndef BASECAMERA_JPL_HPP
#define BASECAMERA_JPL_HPP

#include "../math/matrix/mat4/Matrix4.h"
#include "../math/vector/quaternion/Quaternion.h"
#include "../math/vector/v3/Vector3f.h"
#include "../utils/WindowInfo.hpp"

namespace jpl{

    class BaseCamera{

        protected:

            float near, far, FOV;
            float viewportW, viewportH;
            jgl::Matrix4* combined, *projection, *view;
            jgl::Vector3f* direction, *position, *up, *right; 


            BaseCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far);

        public:

            /**
             * Normalizes the up vector.
             * Calculates the right vector via a crs(direction, up)
             * Then recalculating the up vector via a crs(right, direction).
             */ 
            virtual void normalizeUpAndRight();

            /**
             * Set direction vector to look at x,y,z
             * @param x
             * @param y
             * @param z
             */ 
            virtual void lookAt(float x, float y, float z);


            /**
             * Set direction vector to look at given position vector
             * @param target
             */ 
            virtual void lookAt(jgl::Vector3f* target);

            
            /**
             * Alterate near and far value of this camera
             * @param near
             * @param far
             */ 
            virtual void setPlane(float near, float far);

            /**
             * Set a new FieldOfView
             * @param FOV
             */ 
            void setFOV(float FOV); 

            /**
             * Recalculate view and combined matrix
             */ 
            virtual void update();

            /**
             * Update projection matrix.
             * This should be called after have either resized window, viewports, changed FOV or z-depth
             */ 
            virtual void updateFrustum();


            jgl::Matrix4* getViewMatrix();
            jgl::Matrix4* getProjectionMatrix();
            jgl::Matrix4* getCombinedMatrix();
            jgl::Vector3f* getDirection();
            jgl::Vector3f* getPosition();
            jgl::Vector3f* getUp();
            float getFar();
            float getNear();
            float getViewportH();
            float getViewportW();

    };

}

#endif