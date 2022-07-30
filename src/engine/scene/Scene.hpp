/**
 * This is a simple abstraction a scene.
 * It contains everything that is rendered each game tick.
 * 
 * In your Client's Main you should have only one instance per time of this.
 * Override tick() method in you sub-class and make call it by the render loop 
 * 
 * e.g.
 *  MainMenuScene.class (let's render SinglePlayer button, Multiplayer one ecc... by tick()).
 *  Let's instance it in main.cpp and call tick() in the render loop
 * 
 * Since super-constructor increases lastID, you must call it by sub-constructor
 * 
 * @author gabriele-P03 (pacegabriele@libero.it)
 */

#ifndef SCENE_JPL
#define SCENE_JPL

#include <string>

namespace jpl
{


    class Scene
    {
        private:

            //Contains the ID of the last scene instances
            //On each instance it will be increased
            static unsigned int lastID;
            
            unsigned int ID;

            /**
             * Contains the name of the scene
             * You can set the same name of another scene,
             * but you will get the first occurrence by SceneManager#getSceneByName(),
             * so it is very discouraged
             */
            std::string sceneName;
        public:

            Scene(std::string sceneName);
            
            inline virtual void tick(){
                
            }

            unsigned int getID();

            std::string getSceneName();
            void setSceneName(std::string sceneName);

    };

} 

#endif