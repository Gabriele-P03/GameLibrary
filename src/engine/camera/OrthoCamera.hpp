/**
 * The orthographic camera is a camera which is parallel to Z-plane, thus it must be used in 2D game.
 * 
 * Orthographic camera rotates only around Z-axis (Yaw)
 * 
 * @author Gabriele-P03
 */ 

#ifndef ORTHOCAMERA_JPL_HPP
#define ORTHOCAMERA_JPL_HPP

#include "BaseCamera.hpp"
#include "../math/vector/v2/Vector2f.h"
#include "GLFW/glfw3.h"

namespace jpl{

    class OrthoCamera : public BaseCamera{

        private:


        public:

            /**
             * Construct a new Orthographic camera.
             * It call also OrthoCamera#setToOrtho(viewportW, viewportH) and OrthoCamera#update()
             */ 
            OrthoCamera(jgl::Vector3f* position, float near, float far, float viewportW, float viewportH);
            /**
             * Construct a new Orthographic camera with default values of near and far, respectively 0.0f and -10.0f.
             * It call also OrthoCamera#setToOrtho(viewportW, viewportH) and OrthoCamera#update()
             */ 
            OrthoCamera(jgl::Vector3f* position, float viewportW, float viewportH);
            /**
             * Construct a new Orthographic camera with default values of near and far, respectively 0.0f and -10.0f
             * and a position as 0;0;0.
             * It neither call OrthoCamera#setToOrtho(viewportW, viewportH) nor OrthoCamera#update(). You must call them!
             */ 
            OrthoCamera();
            /**
             * Construct a new Orthographic camera.
             * It neither call OrthoCamera#setToOrtho(viewportW, viewportH) nor OrthoCamera#update(). You must call them!
             */ 
            OrthoCamera(float near, float far);
            /**
             * Construct a new Orthographic camera with a position as 0;0;0.
             * It call also OrthoCamera#setToOrtho(viewportW, viewportH) and OrthoCamera#update()
             */ 
            OrthoCamera(float near, float far, float viewportW, float viewportH);


            /**
             * Set the rotation around the Z-axis by the given angle
             */ 
            void setToRotation(float angle);
            /**
             * Rotate this camera by the given angle around Z-axis
             * @param angle
             */
            void rotate(float angle);
            /**
             * Rotate this camera, around the orthographic point described by the given vector, by the given angle
             * @param point
             * @param angle
             */ 
            void rotateAround(jgl::Vector2f* point, float angle);


            /**
             * Update viewports value with the new given ones.
             * This method will not update view matrix, you must call also update()
            */
            void setToOrtho(float newViewportW, float newViewportH);


            /**
             * Translate this camera by the given vector
             * @param translatingVector
             */ 
            void translate(jgl::Vector2f* translatingVector);
            /**
             * Translate this camera by the given vector
             * @param x
             * @param y
             */ 
            void translate(float x, float y);
            /**
             * Set to translation this camera by the given vector
             * @param translationVector
             */
            void setToTranslation(jgl::Vector2f* translationVector); 
            /**
             * Set to translation this camera by the given values
             * @param x
             * @param y
             */
            void setToTranslation(float x, float y); 


            /**
             * Update view and projection matrix
             * Update combined matrix
             */ 
            void update() override;
    };
}

#endif