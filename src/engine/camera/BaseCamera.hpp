/**
 * A BaseCamera is the first abstraction of a camera, it cannot be directly instanced
 * (protected constructors).
 * 
 * If you're developing a 2D game, then use OrthoCamera, otherwise, for 3D, PerspCamera
 * 
 * The combined matrix is already pushed to the current shader program via 
 * pushMatrixCombined(unsigned int shaderProgram) - called by update() which is called by 
 * tick() once camera moves.
 * 
 * Shader's id is passed to tick(), which accept also the speed of movement and rotation one.
 * tick() is the only method you need to call in order to move and rotater camera.
 * 
 * @author Gabriele-P03
 */ 

#ifndef JPL_BASECAMERA_HPP
#define JPL_BASECAMERA_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../utils/WindowSize.hpp"
#include "../input/key/KeyInput.h"

#include <iostream>
namespace jpl{

    class BaseCamera{

        protected:

            BaseCamera(glm::vec3 pos, glm::vec3 target);
            BaseCamera(glm::vec3 pos, glm::vec3 target, float near, float far);
            BaseCamera(glm::vec3 pos, glm::vec3 target, float near, float far, float viewportW, float viewportH);

        public:
            glm::vec3 position, direction, up, right, target;
            float near, far, viewportW, viewportH;
            glm::mat4 view, projection, combined;

            

            /**
             * Update the projection matrix. Not called automatically.
             * Do it once changed eithrt viewport or near or far.
             * 
             * @warning the function in BaseCamera ha an empty body. It will be defined in sub-classes 
             */ 
            virtual void updateFrustum();

            /**
             * update combined matrix. It calls also updateView().
             * Not called automatically. Do it when camera moves or rotates.
             * It also pushes the new combined matrix to the OpenGL pipeline
             * of the current shader program
             * 
             * Pass 0 as shaderProgram if you do not wanna call pushCombinedMatrix()
             * 
             * @param shaderProgram id of the current shader program. 
             */ 
            virtual void update(unsigned int shaderProgram);

            /**
             * This is the main camera's function. It listen for WASD keys
             * in order to move camera
             * 
             * @param speedMov movement speed
             * @param speedRot rotation speed
             * @param shaderProgram id of the current shader program
             */ 
            virtual void tick(float speedMov, float speedRot, unsigned int shaderProgram);

            /**
             * @param viewportW 
             * @param viewportH
             */ 
            void setViewport(float viewportW, float viewportH);

            /**
             * Called by update(), it updates view matrix
             */ 
            virtual void updateView();

            /**
             * Called by constructor and when camera rotates, it updates up and right vectors
             */ 
            virtual void updateUpAndRight();

            /**
             * Push the new combined matrix to the current shader program pipeline
             * You do not need to call it. It's already done by update().
             * 
             * @param shaderProgram id of the current shader program
             */ 
            virtual void pushCombinedMatrix(unsigned int shaderProgram);

    };
}

#endif