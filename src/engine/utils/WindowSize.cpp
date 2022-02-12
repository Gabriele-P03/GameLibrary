#include "WindowSize.hpp"

jpl::WindowSize::WindowSize(){
    w = 0;
    h = 0;
}

jpl::WindowSize jpl::WindowSize::INSTANCE = jpl::WindowSize();