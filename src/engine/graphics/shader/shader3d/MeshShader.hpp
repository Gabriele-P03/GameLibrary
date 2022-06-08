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
#include "../../../math/matrix/mat4/Matrix4.h"

namespace jpl{

    class MeshShader: protected Shader{

        protected:

            jgl::Matrix4* scale, *rotation;

            unsigned int* UBO;

            virtual void bind(const jpl::Mesh* mesh); 
            
        public:

            MeshShader(std::string* pathToVertex, std::string* pathToFragment);

            virtual void draw(jpl::Mesh* mesh, jgl::Matrix4* combined, float x, float y, float z);

            
    };
}

#endif