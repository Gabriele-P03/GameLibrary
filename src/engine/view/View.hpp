/**
 * A view is a simple abstraction of a widget
 * e.g. Button, TextField ecc...
 * 
 *@author Gabriele-P03 
 */

#ifndef VIEW_JPL
#define VIEW_JPL

#include <functional>

namespace jpl{

    class View{

        private:

            int x, y, w, h;
            std::function<void(View*)> listener;

        public:

            View(int x, int y, int w, int h);

            inline virtual void tick();

            virtual void setOnClickListener(std::function<void(View*)> listener);

            int getX();
            int getY();
            int getW();
            int getH();
    };
}

#endif