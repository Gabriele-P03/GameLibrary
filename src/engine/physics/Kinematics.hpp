/**
 * A set of function relative to kinematics
 * 
 * @author Gabriele-P03
 */ 

#ifndef KINEMATICS_JPL
#define KINEMATICS_JPL


#define _USE_MATH_DEFINES
#include <cmath>

#define _USE_PHYSICS_STRUCT_JPL
#include "const_physics.hpp"


/**
 * Define what you need before including this header file
 * 
 *      #define UMR_JPL         //Uniform  Rectilinear Motion
 *      #define UARM_JPL        //uniformly accelerated rectilinear motion
 *      #define UARM_JPL        //uniform circular motion
 *      #define PM_JPL          //parabolic motion
 *      #define HM_JPL          //harmonic motion
 */
namespace jpl{
 
    /**
     * Linear movement: uniform motion in a straight line
     * 
     * @param space
     * @param time
     * 
     * @return average velocity
     */ 
    inline float velocity(float space, float time){
        return space/time;
    }

    /**
     * 
     * @param velocity
     * @param time
     * 
     * @return acceleration
     */ 
    inline float acceleration(float velocity, float time){
        return velocity/time;
    }

    //Uniform Rectilinear Motion
    #ifdef URM_JPL

        /**
         * @param velocity
         * @param t time
         * @param s0 initial distance traveled
         * 
         * @return distance traveled 
         */ 
        inline float URM_equationMotion(float v, float t, float s0){
            return v*t + s0;
        }

    #endif


    //Uniformly Accelereted Rectilinear Motion 
    #ifdef UARM_JPL

        /**
         * @param a acceleration
         * @param v0 initial speed
         * @param t time
         * @param s0 initial distance traveled
         * 
         * @return distance traveled
         */ 
        inline float UARM_equationMotion(float a, float v0, float t, float s0){
            return (a*t*t)/2.0f + v0*t + s0;
        }

        /**
         * @param a acceleration
         * @param v0 initial speed
         * @param t time
         * 
         * @return body's speed after it has been accelerated for a certain period
         */ 
        inline float UARM_velocity(float a, float v0, float t){
            return v0 + a*t;
        }
    #endif


    //Uinform Circular Motion
    #ifdef UCM_JPL

        /**
         * If you wanna calculate angular velocity, then pass 1 as r
         * 
         * @param r radius
         * @param t time
         * 
         * @return velocity of the uniform circular motion
         */ 
        inline float UCM_velocity(float r, float t){
            return 2*M_PI*r/t;
        }

        /**
         * If you wanna calculare angular period, then pass 1 as r
         *  
         * @param r radius
         * @param v velocity
         * 
         * @return period
         */ 
        inline float UCM_time(float r, float v){
            return 2*M_PI*r/v;
        }

        /**
         * If you pass an angular velocity as v, you will get 1
         * 
         * @param v velocity
         * @param t time
         * 
         * @return radius
         */ 
        inline float UCM_radius(float v, float t){
            return v*t/(2*M_PI);
        }

        /**
         * If you pass an angular velocity, then pass 1.0f/r as r 
         *
         * @param v speed of the UCM
         * @param r radius
         * @param dir direction from center of the circus towards body
         * 
         * @return a physic vector containing the orthogonal direction and magnitute
         */ 
        inline vector_f* UCM_centripetal(float v, float r, glm::vec3 dir){

            glm::vec3 right_ortho = glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec3 new_up = glm::cross(right_ortho, dir);
            glm::vec3 new_right = glm::cross(dir, new_up);
            new_right = glm::normalize(new_right);

            return new vector_f(new_right, v*v*r);
        }


    #endif

    //Parabolic Motion
    #if defined (PM_JPL) && defined (_USE_PHYSICS_DEFINES_JPL)

        /**
         * @param G gravity
         * @param angle angle
         * @param v0 initial speed
         * @param t time
         * @param x0 initial space traveled on X
         * @param y0 initial space traveled on Y
         */ 
        inline glm::vec3 PM(GRAVITY G, float angle, float v0, float t, float x0, float y0){
            
            float V0x = v0*cos(angle);
            float V0y = v0*sin(angle);

            float x = x0 + V0x*t;
            float y = (-G*t*t)/2.0f + V0y*t + y0;

            return glm::vec3(x, y, 0.f);
        }
    #endif

    //Harmonic Motion
    #ifdef HM_JPL

        /**
         * @param p pulsation
         * @param a acceleration (1.0f if not accelerated)
         * @param t time
         * @param ph phase (initial x coord, pass 0.0f if he motion must begin from right)
         * 
         * @return x coord of the harmonic motion
         */ 
        inline float HM(float p, float a, float t, float ph){
            return a * cos(p*t + ph);
        }
    #endif

}

#endif