/**
 * This is a basic abrìstraction a shader which renders a normal cube.
 * 
 * Constructor set the 8 vertices (then 8 vertices * 3 float = 24 float) whose cube is composed of 
 * 
 * @author Gabriele-P03
 */ 

#ifndef CUBESHADER_HPP
#define CUBESHADER_HPP

#include "../Shader.h"

namespace jpl{

    class CubeShader : public Shader{

        public:

            CubeShader();

    };
}

#endif