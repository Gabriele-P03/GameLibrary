/**
 *
 * This header file has been written for providing, as public static field,
 * width and height of the window 
 * 
 * The size of the window are automatically update by the size callback
 * @see WindowInfo.cpp
 * 
 * @author Gabriele-P03
 */ 

#ifndef WINDOWSIZE_JPL_HPP
#define WINDOWSIZE_JPL_HPP

namespace jpl{

    class WindowSize
    {

        private:
            WindowSize();

        public:

            int w, h;
            static WindowSize INSTANCE;

    };
}

#endif