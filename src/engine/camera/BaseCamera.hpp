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

namespace jpl{

    class BaseCamera{

        private:

            float near, far;
            float viewportW, viewportH;
            jgl::Matrix4* combined, *projection, *view;
            jgl::Vector3f* direction, *position, *up; 

        public:

            BaseCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far);

            /**
             * Set direction vector to look at x,y,z
             * @param x
             * @param y
             * @param z
             */ 
            void lookAt(float x, float y, float z);

            /**
             * Set direction vector to look at given position vector
             * @param target
             */ 
            void lookAt(jgl::Vector3f* target);

            /**
             * Normalizes the up vector.
             * Calculates the right vector via a crs(direction, up)
             * Then recalculating the up vector via a crs(right, direction).
             */ 
            void normalizeUp();

            /**
             * Projects the given Vector4 in world space to screen coordinates
             * @param worldCoords
             */ 
            jgl::Vector3f* project(jgl::Vector3f* worldCoords);

            /**
             * Rotate this camera by the given rotation matrix
             * @param rotationMatrix
             */ 
            void rotate(jgl::Matrix4* rotationMatrix);

            /**
             * Rotate this camera by the given rotation matrix
             * @param quaternion
             */ 
            void rotate(jgl::Quaternion* quaternion);

            /**
             * Rotate this camera around the given point
             * @param point
             * @param rotationMatrix
             */ 
            void rotateAround(jgl::Vector3f* point, jgl::Matrix4* rotationMatrix);

            /**
             * Transform the position, direction and up vector by the given transformation matrix
             * @param transformationMatrix
             */ 
            void transform(jgl::Matrix4* transformationMatrix);

            /**
             * Translate this camera by the given vector
             * @param translatingVector
             */ 
            void translate(jgl::Vector3f* translatingMatrix);

            /**
             * Inverse of BaseCamera#project(jgl::Vector3i*)
             * @param screenCords
             * @return world space coords from the given screen one
             */ 
            jgl::Vector3f* unproject(jgl::Vector3f* screenCords);

            /**
             * Recalculate projection and view matrix
             */ 
            void update();
    };

}

#endif