/**
 * A mesh is a collection of vertices and elements which compose a 3D object
 * No shader will be used in 2D Game. On the other hand it will always used for 3D.
 * 
 * If you need to load a 3D model from a file object, yous should really consider to get 
 * an instance of this class via ModelLoader().
 * 
 * As I worked out with a 3D game based on cubes, this class contains a static instance of Mesh
 * 
 * @author Gabriele-P03
 */ 

#ifndef MESH_JPL_HPP
#define MESH_JPL_HPP

namespace jpl{

    class Mesh{

        private:
            unsigned int _sizeVertices;
            float* vertices;

            unsigned int* indices;
            unsigned int _sizeIndices;

        public:

            Mesh(float* vertices, unsigned int _sizeVertices, unsigned int* indices, unsigned int _sizeIndices);
            
            float* getVertices() const;
            unsigned int getSizeVertices() const;
            unsigned int* getIndices() const;
            unsigned int getSizeIndices() const;

            static const Mesh* CUBE;
    };
}

#endif