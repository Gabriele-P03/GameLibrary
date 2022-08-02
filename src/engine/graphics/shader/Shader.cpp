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
    this->initializeVectors();
}

jpl::Shader::Shader(const char* vertexCode, const char* fragmentCode){
    this->genMainBuffers();
    this->createShader(std::string(vertexCode), std::string(fragmentCode));
    this->initializeVectors();
}

void jpl::Shader::genMainBuffers(){
    jpl::Logger::INSTANCE->print("Generating new shader...");

    //Gen VBO
    VBOs.push_back(new unsigned int);
    glGenBuffers(1, VBOs[VBOs.size()-1]);
    this->VBO = VBOs[VBOs.size()-1];

    //Gen VAO
    VAOs.push_back(new unsigned int);
    glGenVertexArrays(1, VAOs[VAOs.size()-1]);
    this->VAO = VAOs[VAOs.size()-1];

    //Gen EBO
    EBOs.push_back(new unsigned int);
    glGenBuffers(1, EBOs[EBOs.size()-1]);
    this->EBO = EBOs[EBOs.size()-1];
}

void jpl::Shader::createShader(std::string vertexCode, std::string fragmentCode){

    //Creating and compiling vertex shader
    jpl::Logger::INSTANCE->print("Compiling vertex...");
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
        jpl::Logger::INSTANCE->print("Error during compile vertex shader" + std::string(infoLog) + "Code: " + std::string(vertexCode));
        exit(-1);
    }

    //Creating and compiling fragment shader
    jpl::Logger::INSTANCE->print("Compling fragment...");
    fragmentShaders.push_back(new unsigned int(glCreateShader(GL_FRAGMENT_SHADER)));

    buffer = fragmentCode.c_str();

    this->fragmentShader = fragmentShaders[fragmentShaders.size()-1];
    glShaderSource(*this->fragmentShader, 1, &buffer, NULL);
    glCompileShader(*this->fragmentShader);

    glGetShaderiv(*this->fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(*this->fragmentShader, 512, NULL, infoLog);
        jpl::Logger::INSTANCE->print("Error during compile fragment shader" + std::string(infoLog) + "Code: " + std::string(fragmentCode));
        exit(-1);
    }

    if(success){
        shaderPrograms.push_back(new unsigned int(glCreateProgram()));
        this->shaderProgram = shaderPrograms[shaderPrograms.size()-1];

        jpl::Logger::INSTANCE->print("Attaching vertex to shader...");
        glAttachShader(*this->shaderProgram, *this->vertexShader);
        jpl::Logger::INSTANCE->print("Attaching fragment to shader...");
        glAttachShader(*this->shaderProgram, *this->fragmentShader);
        jpl::Logger::INSTANCE->print("Linking...");
        glLinkProgram(*this->shaderProgram);

        glGetProgramiv(*this->shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(*this->shaderProgram, 512, NULL, infoLog);
            jpl::Logger::INSTANCE->print("Error during linking shader program: " + std::string(infoLog));
            exit(-1);
        }
    }

    jpl::Logger::INSTANCE->print("New shader created...");
}

void jpl::Shader::initializeVectors(){
    this->rotation = glm::mat4(1.0f);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->translation = glm::vec3(0.0f, 0.0f, 0.0f);
}

void jpl::Shader::pushMatrixTransformation(){
    glm::mat4 transform = glm::translate(this->rotation, this->translation);
    transform = glm::scale(transform, this->scale);
    glUniformMatrix4fv(glGetUniformLocation(*this->getShaderProgram(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));
}

void jpl::Shader::updateUpAndRight(){
    glm::vec3 direction = glm::axis(glm::quat_cast(this->rotation));
    this->right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    this->up = glm::cross(direction, right);
}

void termShaders(){

    jpl::Logger::INSTANCE->print("Terminating Shaders...Unbinding current buffer and array");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    jpl::Logger::INSTANCE->print("Amount of vertex shaders to delete: " + jpl::Shader::getVertexShaders()->size());
    for(int i = 0; i < jpl::Shader::getVertexShaders()->size(); i++){
        glDeleteShader(*jpl::Shader::getVertexShaders()->at(i));
    }

    jpl::Logger::INSTANCE->print("Amount of fragment shaders to delete: " + jpl::Shader::getFragmentShaders()->size());
    for(int i = 0; i < jpl::Shader::getFragmentShaders()->size(); i++){
        glDeleteShader(*jpl::Shader::getFragmentShaders()->at(i));
    }

    jpl::Logger::INSTANCE->print("Amount of arrays to delete: " + jpl::Shader::getVAOs()->size()) ;
    glDeleteVertexArrays(jpl::Shader::getVAOs()->size(), jpl::Shader::getVAOs()->at(0));

    jpl::Logger::INSTANCE->print("Amount of buffers to delete: " + jpl::Shader::getVBOs()->size()) ;
    glDeleteBuffers(jpl::Shader::getVBOs()->size(), jpl::Shader::getVBOs()->at(0));

    jpl::Logger::INSTANCE->print("Amount of elements buffer to delete: " + jpl::Shader::getEBOs()->size()) ;
    glDeleteBuffers(jpl::Shader::getEBOs()->size(), jpl::Shader::getEBOs()->at(0));

    jpl::Logger::INSTANCE->print("Deleting shader...");
    for(int i = 0; i < jpl::Shader::getShaderPrograms()->size(); i++){
        glDeleteProgram(*jpl::Shader::getShaderPrograms()->at(i));
    }

    jpl::Logger::INSTANCE->print("Shaders terminated");
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
