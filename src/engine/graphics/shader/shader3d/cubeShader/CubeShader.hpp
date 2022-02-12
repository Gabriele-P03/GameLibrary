/**
 * This is a basic abstraction a shader which renders a normal cube.
 * 
 * Constructor set the 8 vertices (then 8 vertices * 3 float = 24 float) whose cube is composed of 
 * 
 * @author Gabriele-P03
 */ 

#ifndef CUBESHADER_HPP
#define CUBESHADER_HPP

#include "../MeshShader.hpp"
#include "../../../../math/matrix/mat4/Matrix4.h"

namespace jpl{

    class CubeShader : public MeshShader{

        private:

            virtual void draw() override;

        public:

            jgl::Matrix4* scale, *translating, *rotation;

            CubeShader();

            virtual void draw(jgl::Matrix4* combined, float x, float y, float z);
    };
}

#endif