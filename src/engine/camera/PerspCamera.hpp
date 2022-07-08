/**
 * @author Gabriele-P03 
 */ 

#ifndef JPL_PERSPCAMERA_HPP
#define JPL_PERSPCAMERA_HPP

#include "BaseCamera.hpp"

namespace jpl{

    class PerspCamera : public BaseCamera{

        private: 
            float FOV;

        public:

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