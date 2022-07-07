/**
 * This is the Orthographic Camera which is used for 2D games based on X and Y coords.
 * 
 * 
 * An ortho camera generally works with WASD combination
 */ 

#ifndef JPL_ORTHOCAMERA_HPP
#define JPL_ORTHOCAMERA_HPP

#include "BaseCamera.hpp"

namespace jpl{

    class OrthoCamera : public BaseCamera{

        protected:

        public:
            OrthoCamera(glm::vec3 pos, glm::vec3 target, float near, float far, float viewportW, float viewportH);
            OrthoCamera(glm::vec3 pos, glm::vec3 target, float near, float far);
            OrthoCamera(glm::vec3 pos, glm::vec3 target);

            virtual void updateFrustum() override;
            virtual void tick(float speedMov, float speedRot, unsigned int shaderProgram) override;
    };
}

#endif