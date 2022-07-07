#include "Shader.hpp"


std::vector<unsigned int*> jpl::Shader::VBOs;
std::vector<unsigned int*> jpl::Shader::VAOs;
std::vector<unsigned int*> jpl::Shader::EBOs;
std::vector<unsigned int*> jpl::Shader::vertexShaders;
std::vector<unsigned int*> jpl::Shader::fragmentShaders;
std::vector<unsigned int*> jpl::Shader::shaderPrograms;

jpl::Shader::Shader(std::string pathToVertexFile, std::string pathToFragmentFile){

    this->genMainBuffers();
    this->createShader(*readFile(pathToVertexFile), *readFile(pathToFragmentFile));
    this->initializeMatrices();
}

jpl::Shader::Shader(const char* vertexCode, const char* fragmentCode){
    this->genMainBuffers();
    this->createShader(std::string(vertexCode), std::string(fragmentCode));
    this->initializeMatrices();
}

void jpl::Shader::genMainBuffers(){
    std::cout<<"Generating new shader...Buffer...";

    //Gen VBO
    VBOs.push_back(new unsigned int);
    glGenBuffers(1, VBOs[VBOs.size()-1]);
    this->VBO = VBOs[VBOs.size()-1];

    //Gen VAO
    std::cout<<"Arrays...";
    VAOs.push_back(new unsigned int);
    glGenVertexArrays(1, VAOs[VAOs.size()-1]);
    this->VAO = VAOs[VAOs.size()-1];

    //Gen EBO
    std::cout<<"Elements\n";
    EBOs.push_back(new unsigned int);
    glGenBuffers(1, EBOs[EBOs.size()-1]);
    this->EBO = EBOs[EBOs.size()-1];
}

void jpl::Shader::createShader(std::string vertexCode, std::string fragmentCode){

    //Creating and compiling vertex shader
    std::cout<<"Compiling vertex...";
    vertexShaders.push_back(new unsigned int(glCreateShader(GL_VERTEX_SHADER)));
    this->vertexShader = vertexShaders[vertexShaders.size()-1];

    const char* buffer = vertexCode.c_str();

    glShaderSource(*this->vertexShader, 1, &buffer, NULL);
    glCompileShader(*this->vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(*this->vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(*this->vertexShader, 512, NULL, infoLog);
        std::cout<<"Error during compile vertex shader"<<infoLog<<"\nCode: "<<std::string(vertexCode);
        exit(-1);
    }

    //Creating and compiling fragment shader
    std::cout<<"Compling fragment...";
    fragmentShaders.push_back(new unsigned int(glCreateShader(GL_FRAGMENT_SHADER)));

    buffer = fragmentCode.c_str();

    this->fragmentShader = fragmentShaders[fragmentShaders.size()-1];
    glShaderSource(*this->fragmentShader, 1, &buffer, NULL);
    glCompileShader(*this->fragmentShader);

    glGetShaderiv(*this->fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(*this->fragmentShader, 512, NULL, infoLog);
        std::cout<<"Error during compile fragment shader"<<infoLog<<"\nCode: "<<std::string(fragmentCode);
        exit(-1);
    }

    if(success){
        shaderPrograms.push_back(new unsigned int(glCreateProgram()));
        this->shaderProgram = shaderPrograms[shaderPrograms.size()-1];

        std::cout<<"Attaching vertex to shader...";
        glAttachShader(*this->shaderProgram, *this->vertexShader);
        std::cout<<"Attaching fragment to shader...";
        glAttachShader(*this->shaderProgram, *this->fragmentShader);
        std::cout<<"Linking...";
        glLinkProgram(*this->shaderProgram);

        glGetProgramiv(*this->shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(*this->shaderProgram, 512, NULL, infoLog);
            std::cout<<"Error during linking shader program: "<<infoLog<<"\n";
            exit(-1);
        }
    }

    std::cout<<"New shader created...\n";
}

void jpl::Shader::initializeMatrices(){
    this->rotation = glm::mat4(1.0f);
    this->scale = glm::mat4(1.0f);
    this->translation = glm::mat4(1.0f);
}

inline void jpl::Shader::bind(){
    
    //Check if this shader's objects are already bind
    int currentVAO;
    glGetProgramiv(*this->shaderProgram, GL_ARRAY_BUFFER_BINDING, &currentVAO);
    if(currentVAO != *this->VAO){

        //Before binding buffer(s), it's gonna binding array
        glBindVertexArray(*this->VAO);

        this->bindVBO();
        this->bindEBO();
        this->vertexAttrib();

        glBindVertexArray(0);
    }
}

inline void jpl::Shader::bindVBO(){
    glBindBuffer(GL_ARRAY_BUFFER, *this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->_sizeVertices * sizeof(vertices), vertices, GL_STATIC_DRAW);
}

inline void jpl::Shader::bindEBO(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_sizeIndices * sizeof(indices), indices, GL_STATIC_DRAW);
}

inline void jpl::Shader::vertexAttrib(){
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

inline void jpl::Shader::draw(){
    this->useProgram();
    this->bind();
    glBindVertexArray(*this->VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
}

inline void jpl::Shader::useProgram(){

    //Retrieve the current shader program in order to not call glUseProgram()
    int currentId;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentId);

    if(currentId != *this->shaderProgram)
        glUseProgram(*this->shaderProgram);
}

void jpl::Shader::pushMatrixTransformation(){
    glm::mat4 transform = this->translation * this->scale * this->rotation;
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));
}

void termShaders(){

    std::cout<<"Terminating Shaders...\n\nUnbinding current buffer and array\n";

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    std::cout<<"Amount of vertex shaders to delete: "<<jpl::Shader::getVertexShaders()->size();
    for(int i = 0; i < jpl::Shader::getVertexShaders()->size(); i++){
        glDeleteShader(*jpl::Shader::getVertexShaders()->at(i));
    }

    std::cout<<"Amount of fragment shaders to delete: "<<jpl::Shader::getFragmentShaders()->size()<<std::endl;
    for(int i = 0; i < jpl::Shader::getFragmentShaders()->size(); i++){
        glDeleteShader(*jpl::Shader::getFragmentShaders()->at(i));
    }

    std::cout<<"Amount of arrays to delete: "<<jpl::Shader::getVAOs()->size()<<std::endl;
    glDeleteVertexArrays(jpl::Shader::getVAOs()->size(), jpl::Shader::getVAOs()->at(0));

    std::cout<<"Amount of buffers to delete: "<<jpl::Shader::getVBOs()->size()<<std::endl;
    glDeleteBuffers(jpl::Shader::getVBOs()->size(), jpl::Shader::getVBOs()->at(0));

    std::cout<<"Amount of elements buffer to delete: "<<jpl::Shader::getEBOs()->size()<<std::endl;
    glDeleteBuffers(jpl::Shader::getEBOs()->size(), jpl::Shader::getEBOs()->at(0));

    std::cout<<"Deleting shader...\n";
    for(int i = 0; i < jpl::Shader::getShaderPrograms()->size(); i++){
        glDeleteProgram(*jpl::Shader::getShaderPrograms()->at(i));
    }

    std::cout<<"Shaders terminated\n\n";
}

unsigned int* jpl::Shader::getVBO(){return this->VBO;}
unsigned int* jpl::Shader::getVAO(){return this->VAO;}
unsigned int* jpl::Shader::getEBO(){return this->EBO;}
unsigned int* jpl::Shader::getVertexShader(){return this->vertexShader;}
unsigned int* jpl::Shader::getFragmentShader(){return this->fragmentShader;}
unsigned int* jpl::Shader::getShaderProgram(){return this->shaderProgram;}

std::vector<unsigned int*>* jpl::Shader::getVBOs(){return &jpl::Shader::VBOs;}
std::vector<unsigned int*>* jpl::Shader::getVAOs(){return &jpl::Shader::VAOs;}
std::vector<unsigned int*>* jpl::Shader::getEBOs(){return &jpl::Shader::EBOs;}
std::vector<unsigned int*>* jpl::Shader::getVertexShaders(){return &jpl::Shader::vertexShaders;}
std::vector<unsigned int*>* jpl::Shader::getFragmentShaders(){return &jpl::Shader::fragmentShaders;}
std::vector<unsigned int*>* jpl::Shader::getShaderPrograms(){return &jpl::Shader::shaderPrograms;}

float* jpl::Shader::getVertices(){return this->vertices;}
unsigned int jpl::Shader::getSizeVertices(){return this->_sizeVertices;}
void jpl::Shader::setVertices(float* _buffer, unsigned int _sizeBuffer){this->vertices = _buffer; this->_sizeVertices = _sizeBuffer;}

unsigned int* jpl::Shader::getIndices(){return this->indices;}
unsigned int jpl::Shader::getSizeIndices(){return this->_sizeIndices;}
void jpl::Shader::setIndices(unsigned int* _buffer, unsigned int _sizeBuffer){this->indices = _buffer; this->_sizeIndices = _sizeBuffer;}
