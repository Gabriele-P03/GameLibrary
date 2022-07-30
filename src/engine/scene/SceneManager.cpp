#include "SceneManager.hpp"

jpl::SceneManager::SceneManager(){

}

bool jpl::SceneManager::setIDScene(unsigned int sceneID){

    for(int i = 0; i < this->SCENES.size(); i++){
        if(this->SCENES[i]->getID() == sceneID){
            this->currentSceneID = sceneID;
            this->currentSceneID_inVector = i;
            return true;
        }
    }

    return false;
}

unsigned int jpl::SceneManager::getIDScene(){return this->currentSceneID;}

bool jpl::SceneManager::addScene(Scene* newScene){
    for(Scene* scene : this->SCENES){
        if(scene->getID() == newScene->getID()){
            return false;
        }
    }

    this->SCENES.push_back(newScene);
    return true;
}

unsigned int jpl::SceneManager::getSceneByName(std::string sceneName){
    for(int i = 0; i < this->SCENES.size(); i++){
        if(this->SCENES[i]->getSceneName() == sceneName){
            return i;
        }
    }

    return 0;
}

jpl::Scene* jpl::SceneManager::getSceneByID(unsigned int IDScene){
    for(Scene* scene : this->SCENES){
        if(scene->getID() == IDScene){
            return scene;
        }
    }

    return nullptr;
}

bool jpl::SceneManager::removeSceneByID(unsigned int sceneID){

    for(unsigned int i = 0; i < this->SCENES.size(); i++){
        if(this->SCENES[i]->getID() == sceneID){
            this->SCENES.erase(this->SCENES.begin() + i);
            return true;
        }
    }

    return false;
}