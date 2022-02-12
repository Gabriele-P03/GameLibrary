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
            jgl::Vector3f* direction, *position, *up; 


            BaseCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far);


            /**
             * Normalizes the up vector.
             * Calculates the right vector via a crs(direction, up)
             * Then recalculating the up vector via a crs(right, direction).
             */ 
            virtual void normalizeUp();

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
             * Translate this camera by the given vector
             * @param translatingVector
             */ 
            virtual void translate(jgl::Vector3f* translatingVector);
            /**
             * Set to translation this camera by the given vector
             * @param translatingVector
             */ 
            virtual void setToTranslation(jgl::Vector3f* translatingVector);


        public:

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
             * Projects the given Vector4 in world space to screen coordinates
             * This method return a nullptr when called by BaseCamera
             * @param worldCoords
             */ 
            virtual jgl::Vector3f* project(jgl::Vector3f* worldCoords);
            /**
             * Inverse of BaseCamera#project(jgl::Vector3i*)
             * This method return a nullptr when called by BaseCamera
             * @param screenCords
             * @return world space coords from the given screen one
             */ 
            virtual jgl::Vector3f* unproject(jgl::Vector3f* screenCords);
            
            /**
             * Alterate near and far value of this camera
             * @param near
             * @param far
             */ 
            virtual void setPlane(float near, float far);

            /**
             * Recalculate projection and view matrix
             */ 
            virtual void update();

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