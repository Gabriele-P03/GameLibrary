/**
 * A ModelShader is a shader which renders wavefront model as mesh.
 * You can load your own model by loadModel(), getting a new instance of Mesh
 * 
 * @author Gabriele-P03
 */ 

#ifndef JPL_MODELSHADER_HPP
#define JPL_MODELSHADER_HPP

#include "Shader.hpp"
#include "../model/Mesh.hpp"

namespace jpl{
    
    class ModelShader : public Shader{


        public:
            ModelShader();
            ModelShader(std::string pathToVertex, std::string pathToFragment);

            void render(Mesh* mesh, float x, float y, float z);
    };
} 


#endif