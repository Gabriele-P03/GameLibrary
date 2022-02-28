/**
 * MeshShader is the first abstraction of shader which should use for 3D rendering.
 * As its name says, it uses Mesh as a collection of vertices, vertices textures and indices
 * 
 * @author Gabriele-P03 
 */ 

#ifndef MESHSHADER_JPL_HPP
#define MESHSHADER_JPL_HPP

#include "../Shader.h"
#include "../../model/Mesh.hpp"

namespace jpl{

    class MeshShader: protected Shader{

        protected:

            unsigned int* UBO;

            MeshShader(std::string* pathToVertex, std::string* pathToFragment);

            virtual void draw() override;

            virtual void bind(const jpl::Mesh* mesh); 
    };
}

#endif