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

        private:

            unsigned int currentIDMesh;

        public:
            ModelShader();
            ModelShader(std::string pathToVertex, std::string pathToFragment);

            void setMesh(Mesh* mesh);

            inline void render(Mesh* mesh, float x, float y, float z){

                x *= jpl::WindowSize::INSTANCE.w/jpl::MAX_WINDOW_W;
                y *= jpl::WindowSize::INSTANCE.h/jpl::MAX_WINDOW_H;
                
                this->useProgram();

                //As model which is not a cube, or kinda of, it hardly ever will use indices
                //We can check it via mesh->getIndices() != nullptr
                glBindVertexArray(*this->VAO);

                this->translation.x = x;
                this->translation.y = y;
                this->translation.z = z;

                this->pushMatrixTransformation();

                if(mesh->getIndices() != nullptr){  
                    glDrawElements(GL_TRIANGLES, mesh->getSizeIndices(), GL_UNSIGNED_INT, (void*)0);
                }
                else{
                    glDrawArrays(GL_TRIANGLES, 0, mesh->getSizeVertices()/5);
                }
            }
    };
} 


#endif