/**
 * 
 * An header file which contains some const of physics
 * 
 * @author Gabriele-P03
 */ 

#ifndef CONST_PHYSICS_JPL
#define CONST_PHYSICS_JPL

#include <glm/vec3.hpp>

namespace jpl {

    //Generally a force is represented by a direction and a magnitude

    #ifdef _USE_PHYSICS_STRUCT_JPL

    struct vector_f{
        glm::vec3 dir;
        float magnitude;

        vector_f(glm::vec3 dir, float magnitude) : dir(dir), magnitude(magnitude){}
    };

    #endif

    #ifdef _USE_PHYSICS_DEFINES_JPL

        //Gravity

        typedef float GRAVITY;

        const GRAVITY G_EARTH = 9.81;
        const GRAVITY G_MARS  = 3.72;
        const GRAVITY G_MOON =  1.62;


        #define LIGHT_SPEED 300000000   //Light speed is about 299 792 458 m/s. It's been floor

        //Speed sound depends by temperature and composition of the way
        //In the air at 20°C it is about 343 m/s
        #define SOUND_SPEED 343         

    #endif
}

#endif