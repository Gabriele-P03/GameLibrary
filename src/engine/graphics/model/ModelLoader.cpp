#include "ModelLoader.hpp"

jpl::Mesh* jpl::loadModel(std::string* pathToObject){

    std::fstream* file = new std::fstream;
    getInternalFile(pathToObject, std::ios_base::in, &file);
    
    std::vector<float*> vertices;
    std::vector<unsigned int*> indices;
    std::vector<unsigned int*> textures;

    std::string tmp;

    while( std::getline(*file, tmp, '\n') ){
        
        if(tmp.size() > 2){ //Prevent out_of_range
            if(tmp.at(0) == 'v'){
                tmp = tmp.substr(tmp.find_first_of(' ')+1, tmp.size());
                vertices.insert(vertices.begin(), new float(atof(tmp.substr(0, tmp.find_first_of(' ')).c_str())));
                tmp = tmp.substr(tmp.find_first_of(' ')+1, tmp.size());
                vertices.insert(vertices.begin(), new float(atof(tmp.substr(0, tmp.find_first_of(' ')).c_str())));
                vertices.insert(vertices.begin(), new float(atof(tmp.substr(tmp.find_first_of(' ')+1, tmp.size()).c_str())));
            }else if(tmp.substr(0, 2) == "vt"){
                tmp = tmp.substr(tmp.find_first_of(' ')+1, tmp.size());
                textures.insert(textures.begin(), new unsigned int(atoi(tmp.substr(0, tmp.find_first_of(' ')).c_str())));
                textures.insert(textures.begin(), new unsigned int(atoi(tmp.substr(tmp.find_first_of(' '), tmp.size()).c_str())));
            }else if(tmp.at(0) == 'f'){
                computeFace(tmp.substr(2, tmp.size()), vertices, indices, textures);
            }
        }
    }

    return nullptr;
}

void jpl::computeFace(std::string face, std::vector<float*> vertices, std::vector<unsigned int*> indices, std::vector<unsigned int*> textures){

    std::string tmp;
    std::vector<float> bufferVertices;
    std::vector<unsigned int> bufferIndices;
    while(  (tmp = face.substr(0, face.find_first_of(' '))).size() > 0 ){
        
        //Remove the current part working on
        face = face.substr(tmp.size(), face.size());

        //Divide v, vt and vn
        unsigned int v = atoi(tmp.substr(0, tmp.find_first_of('/')).c_str());
        unsigned int vt = atoi(tmp.substr(tmp.find_first_of('/')+1, tmp.find_last_of('/')).c_str());
        //unsigned int vn = atoi(tmp.substr(tmp.find_last_of('/')).c_str());

        bufferVertices.insert(bufferVertices.end(), v);  
    }
}