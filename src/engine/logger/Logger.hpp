/**
 * A logger provides writing on terminal - and once the game has been closed, also in a file -
 * everything that happens during gaming: resource loading, settings loading, errors ecc...
 * 
 * 
 * 
 * @date 2022-08-01
 * @copyright Copyright (c) 2022
 * @author Gabriele-P03
 */

#pragma once

#include "../../files/Files.h"
#include <iostream>
#include <string>

#include <ctime>

namespace jpl{
    
    class Logger{

        private:

            //Return the file name of today e.g. dd-mm-yyyy_hh-mm-ss.txt
            std::string getFileNameOfInstance();

            inline std::tm* getTM(){
                std::time_t now = std::time(0);
                
                return std::localtime(&now);
            }

            std::fstream* file;
            
        public:

            Logger();

            static Logger* INSTANCE;

            /**
             * Print on terminal @msg
             * Write on file the @msg and flushes it
             * @param msg 
             */
            void print(std::string msg);

            /**
             * Close file of printing
             */
            void closeLogger();
    };

} 
