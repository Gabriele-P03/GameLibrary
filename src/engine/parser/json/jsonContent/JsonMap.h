#ifndef JSONMAP_H
#define JSONMAP_H

#include <string>

namespace jpl{


    class JsonMap
    {
        private:
            std::string* key;
            std::string* value;

        public:
            JsonMap(/* args */);
            JsonMap(std::string key, std::string value);
            ~JsonMap();

            std::string* getKey();
            std::string* getValue();

            void setKey(std::string* key);
            void setValue(std::string* value);

            //Parse the given buffer
            void parse(const char* buffer);

            //return this array as string
            std::string str();
    };
  

}


#endif