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

            inline virtual void move(glm::vec3 direction, float speed){
                
                glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));

                //In order to move ignoring y-axis
                right.y = 0.0f;
                right = glm::normalize(right);

                direction = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), right));
                this->position += direction * speed;
            }


        public:
            float YAW, PITCH;
            bool constraintPitch;

            PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far, float viewportW, float viewportH);
            PerspCamera(glm::vec3 pos, glm::vec3 target, float FOV, float near, float far);
            PerspCamera(glm::vec3 pos, glm::vec3 target);

            inline virtual void updateView() override{
                this->view = glm::lookAt(this->position, this->position + this->direction, this->up);
            }

            inline virtual void updateFrustum() override{
                float vW_2 = this->viewportW/2.0f, vH_2 = this->viewportH / 2.0f;
                this->projection = glm::perspective(
                    this->FOV, this->viewportW/this->viewportH, this->near, this->far
                );
            }

            inline virtual void tick(float speedMov, float speedRot, unsigned int shaderProgram) override{
                bool update = false;

                if(jpl::isKeyPressed(GLFW_KEY_W)){
                    this->move(direction, speedMov);
                    update = true;
                }
                if(jpl::isKeyPressed(GLFW_KEY_S)){
                    this->move(direction, -speedMov);
                    update = true;
                }
                if(jpl::isKeyPressed(GLFW_KEY_A)){
                    this->move(glm::cross(this->up, this->direction), speedMov);
                    update = true;
                }
                if(jpl::isKeyPressed(GLFW_KEY_D)){
                    this->move(glm::cross(this->direction, this->up), speedMov);
                    update = true;
                }
                if(jpl::isKeyPressed(GLFW_KEY_SPACE)){
                    this->position.y += speedMov;
                    update = true;
                }
                if(isKeyPressed(GLFW_KEY_LEFT_SHIFT)){
                    this->position.y -= speedMov;
                    update = true;
                }

                //Let's check if mouse has been moved
                double currentX, currentY;
                jpl::getMousePosition(&currentX, &currentY);
                if(this->lastX != currentX || this->lastY != currentY){

                    float yaw = currentX - lastX;
                    float pitch = currentY - lastY;

                    this->YAW += yaw;

                    if(!this->constraintPitch || 
                        (this->constraintPitch && this->PITCH+pitch <= 89.0f && this->PITCH+pitch >= -89.0f))
                        this->PITCH += pitch;


                    this->lastX = currentX;
                    this->lastY = currentY;

                    this->direction.x = cos(glm::radians(this->YAW)) * cos(glm::radians(this->PITCH));
                    this->direction.y = sin(glm::radians(this->PITCH));
                    this->direction.z = sin(glm::radians(this->YAW)) * cos(glm::radians(this->PITCH));

                    this->direction = glm::normalize(this->direction);

                    this->updateUpAndRight();
                    update = true;
                }

                if(update)
                    this->update(shaderProgram);
            }

        

            void setFOV(float FOV);
            float getFOV();
    };   
} 

#endif