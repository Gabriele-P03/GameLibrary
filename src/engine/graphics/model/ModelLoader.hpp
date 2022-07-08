/**
 * This is a 3D .obj model loader.
 * 
 * It parses the .obj file and store faces'
 * 
 * @author Gabriele-P03
 */ 

#ifndef MODEL_LOADER_JPL_HPP
#define MODEL_LOADER_JPL_HPP

#include "Mesh.hpp"
#include "../../../files/Files.h"
#include <vector>


namespace jpl{

    /**
     * @param pathToObject path of the model file to load
     * 
     * @param verticesPerFace how many vertices per face should be loaded (GL_TRIANGLES or GL_QUADS)
     * Notice that if the model file has faces made up of 3 vertices, you must pass GL_TRIANGLES
     * 
     * If your file has face 4 vertices, the first one and the previous one will be copied again 
     * after the fourth vertices in order to complete the other face
     * 
     * @return the mesh with the vertices of the model loaded
     */ 
    jpl::Mesh* loadModel(std::string pathToObject, unsigned int verticesPerFace);


    /**
     * @return vertices-per-face
     */ 
    static int computeFace(std::vector<float*> vertices, std::vector<float*> textures, std::string buffer,
                    std::vector<float*> &verticesMesh, unsigned int verticesPerFace);
}

#endif