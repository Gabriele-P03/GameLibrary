/**
 * A set of function relative to dynamics
 * 
 * @author Gabriele-P03
 */ 

#ifndef DYNAMICS_JPL
#define DYNAMICS_JPL

#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>

#define _USE_PHYSICS_DEFINES_JPL
#define _USE_PHYSICS_STRUCT_JPL
#include "const_physics.hpp"

namespace jpl{

    //First principle of dynamics is theoric

    /**
     * Second principle of dynamics
     * 
     * The change of motion of an object is proportional to the force impressed
     * 
     *  F = m*a
     * 
     * @param directionForce direction of the object/player that impress force
     * @param force 
     * @param mass mass of the object/player that receive the force impressed
     * 
     * @return a vector_force with the same direction of diretionForce and with a magnitude
     */
    inline vector_f* secondPrincipleOfDynamics(glm::vec3 directionForce, float force, float mass){
        return new vector_f(directionForce, mass*force);
    }

    /**
     * Third principle of dynamics
     * 
     * Every action has an equal and an opposite reaction
     * 
     * @param directionForce direction of the object/player that impress force
     * @param force 
     * @param mass mass of the object/player that receive the force impressed
     * @param mass mass of the object/player that impresses the force
     */
    inline vector_f* thirdPrincipleOfDynamics(glm::vec3 directionForce, float force, float mass, float mass1){
        
        glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), directionForce);
        glm::vec3 oppositeDir = glm::cross(right, glm::vec3(0.0f, 1.0f, 0.0f));
        oppositeDir = glm::normalize(oppositeDir);
        
        return new vector_f(oppositeDir, force*mass/mass1);
    }


    /**
     * 
     * @param G gravity
     * @param mass mass of the body
     */ 
    inline vector_f* weight_force(GRAVITY G, float mass){
        return secondPrincipleOfDynamics(glm::vec3(0.0f, -1.0f, 0.0f), G, mass);
    }
}

#endif