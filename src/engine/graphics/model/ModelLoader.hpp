/**
 * 
 */ 

#ifndef MODEL_LOADER_JPL_HPP
#define MODEL_LOADER_JPL_HPP

#include "Mesh.hpp"
#include "../../../files/Files.h"
#include <vector>

namespace jpl{
   
    jpl::Mesh* loadModel(std::string* pathToObject);

    void computeFace(std::string face, std::vector<float*> vertices, std::vector<unsigned int*> indices, std::vector<unsigned int*> textures);
}

#endif