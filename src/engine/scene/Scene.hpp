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
 * 
 * @author gabriele-P03 (pacegabriele@libero.it)
 */

#ifndef SCENE_JPL
#define SCENE_JPL

namespace jpl
{

    class Scene
    {
        
        public:

            Scene();
            
            inline virtual void tick();

    };

} 

#endif