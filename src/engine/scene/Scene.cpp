#include "Scene.hpp"

jpl::Scene::Scene(std::string sceneName){
    jpl::Scene::lastID++;
    this->ID = lastID;

    this->sceneName = sceneName;
}

unsigned int jpl::Scene::getID(){return this->ID;}

std::string jpl::Scene::getSceneName(){return this->sceneName;}
void jpl::Scene::setSceneName(std::string sceneName){this->sceneName = sceneName;}

unsigned int jpl::Scene::lastID = 0;