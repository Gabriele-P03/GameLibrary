#include "ModelLoader.hpp"

jpl::Mesh* jpl::loadModel(std::string pathToObject, unsigned int verticesPerFace){

    
    std::fstream* file = new std::fstream;
    getInternalFile(pathToObject, std::ios_base::in, &file);
    
    std::vector<float*> vertices;
    std::vector<unsigned int*> indices;
    std::vector<float*> textures;

    //The true vector containing vertices and vertices texture of the mesh
    std::vector<float*> verticesMesh;

    std::string buffer;
    unsigned int vpf;

    //This boolean stores if the model loader has finished to load vertices and texture vertices.
    //It is used to reverse the texture vertices vector
    bool startedFace;

    while(getline(*file, buffer)){

        if(buffer.size() > 0){

            std::string type = buffer.substr(0, buffer.find_first_of(' '));
            buffer = buffer.substr(type.size()+1);

            if (type == "v"){
                // A vertice occurs
                vertices.push_back(new float(atof(buffer.substr(0, buffer.find_first_of(' ')).c_str())));
                vertices.push_back(new float(atof(buffer.substr(buffer.find_first_of(' '), buffer.find_last_of(' ')).c_str())));
                vertices.push_back(new float(atof(buffer.substr(buffer.find_last_of(' ')+1).c_str())));
            }else if(type == "vt"){
                textures.push_back(new float(atof(buffer.substr(0, buffer.find_first_of(' ')).c_str())));
                textures.push_back(new float(atof(buffer.substr(buffer.find_last_of(' ')+1).c_str())));
            }else if(type == "f"){

                    /*if(!startedFace){
                        std::reverse(textures.begin(), textures.end());
                        startedFace = true;
                    }*/
                    vpf = computeFace(vertices, textures, buffer, verticesMesh, verticesPerFace);
            }
        }
    }

    return (new jpl::Mesh(verticesMesh))->setVerticesPerFace(vpf);
}

int jpl::computeFace(std::vector<float*> vertices, std::vector<float*> textures, std::string buffer, 
                       std::vector<float*> &verticesMesh, unsigned int verticesPerFace){

    std::string tmp;

    int pos, i = 0;
    do{
        pos = buffer.find(' ');

        tmp = buffer.substr(0, pos > 0 ? pos : buffer.size());

        if(pos > 0){
            buffer = buffer.substr(tmp.size()+1);
        }

        //Let's compute
        int firstSlash = tmp.find_first_of('/');
        int lastSlash = tmp.find_last_of('/');
        int v = atoi(tmp.substr(0, firstSlash).c_str()),
            vt = atoi(tmp.substr(firstSlash+1, lastSlash).c_str()),
            vn = atoi(tmp.substr(lastSlash+1).c_str());

        verticesMesh.push_back(vertices[3*(v-1)]);
        verticesMesh.push_back(vertices[3*(v-1)+1]);
        verticesMesh.push_back(vertices[3*(v-1)+2]);
        verticesMesh.push_back(textures[2*(vt-1)]);
        verticesMesh.push_back(textures[2*(vt-1)+1]);

        //It means that 4 vertices per face model made occurs
       if(++i >= 4 && verticesPerFace == 3){
           int bufferSize = verticesMesh.size();

           verticesMesh.push_back(verticesMesh.at(bufferSize-5-5));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-4));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-3));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-2));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-1));

           verticesMesh.push_back(verticesMesh.at(bufferSize-5-15));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-14));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-13));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-12));
           verticesMesh.push_back(verticesMesh.at(bufferSize-5-11));
       }

    }while (pos > 0);

    return i;   
}

