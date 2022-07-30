/**
 * The SceneManager manages what Scene is rendering at the moment.
 * 
 * Scenes are stored inside an std::vector.
 * 
 * Since every scenes has own ID, SceneManager chooses the one that must be rendered by the
 * ID set via SceneManager#setIDScene(). This will help you to not save a copy of the 
 * cuurent scene, but only its ID
 * 
 * @author Gabriele-P03 
 */
#ifndef SCENEMANAGER_JPL
#define SCENEMANAGER_JPL

#include <iostream>
#include <string>
#include <vector>
#include "Scene.hpp"


namespace jpl{


    class SceneManager{

        private:
            std::vector<Scene*> SCENES;

            //Constains the ID of the current scene
            unsigned int currentSceneID;
            //Contains the index of the current scene in the vector
            unsigned int currentSceneID_inVector;

        public: 

            SceneManager();

            /**
             * It calls tick method of the current scene (ID)
             */
            inline virtual void tick(){

                if(this->currentSceneID_inVector < this->SCENES.size())
                    this->SCENES[this->currentSceneID_inVector]->tick();
            }

            /**
             * Set the scene to be rendered
             * @param sceneID 
             * @return if there's a scene with the given ID 
             */
            bool setIDScene(unsigned int sceneID);
            unsigned int getIDScene();

            /**
             * If the scene has been correctly added to the vector, its indexInVector
             * will be set as std::vector#size() - 1.
             * Use that to set the scene that must be rendered (avoiding getSceneBy___() call)
             * 
             * @param newScene
             * @return if the scene has been added correctly to the vector
             */
            bool addScene(Scene* newScene);

            /**
             * @brief Remove scene by ID
             * 
             * @param sceneID id of the scene to delete 
             * @return if the scene has been removed correctly
             */
            bool removeSceneByID(unsigned int sceneID);

            unsigned int getSceneByName(std::string sceneName);
            Scene* getSceneByID(unsigned int IDScene);


    };
}

#endif