/**
 * A Persp Camera is a perspective camera which is used in 3D game.
 * Since this API has been developed for a thought game, it can be moved only
 * in x and z axis. If you need to move on y one (flying), just override tick() method in 
 * your own sub class of this one.
 * 
 * @warning remember that this camera has been performed for moving with WASD in x and z axis and
 * to rotate of yaw and pitch with the mouse movement.
 * 
 * @warning if you wanna lock pitch (rotating up and down) you must set constraintPitch as true 
 * (which is already done by constructor). An example of game which has locked pitch is Minecraft 
 * 
 * @author Gabriele-P03 
 */ 

#ifndef JPL_PERSPCAMERA_HPP
#define JPL_PERSPCAMERA_HPP

#include "BaseCamera.hpp"
#include "../input/mouse/MouseInput.h"

namespace jpl{

    class PerspCamera : public BaseCamera{

        protected: 
            float FOV;

            float lastX, lastY;

            inline virtual void move(glm::vec3 direction, float speed);


        public:
            float YAW, PITCH;
            bool constraintPitch;

            PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far, float viewportW, float viewportH);
            PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far);
            PerspCamera(glm::vec3 pos, glm::vec3 target);

            virtual void updateView() override;
            virtual void updateFrustum() override;
            virtual void tick(float speedMov, float speedRot, unsigned int shaderProgram) override;

        

            void setFOV(float FOV);
            float getFOV();
    };   
} 

#endif