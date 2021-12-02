#ifndef VECTOR2I_H
#define VECTOR2I_H

#include <string>
#include "../../JMath.h"

namespace jgl{

    class Vector2i
    {
        private:
            int x, y;

        public:   

            Vector2i();
            Vector2i(int x, int y);
            Vector2i(Vector2i* vec2i);
            Vector2i(std::string* fromString);
            
            int getX();
            int getY();

            void setX(int x);
            void setY(int y);
            void set(Vector2i* vec2i);
            void setAll(int x, int y);

            void addX(int x);
            void addY(int y);
            void add(Vector2i* vec2i);
            void addAll(int x, int y);

            void mulX(int x);
            void mulY(int y);
            void mul(Vector2i* vec2i);
            void mulAll(int x, int y);

            Vector2i* cpy();
    
            //Versor of the vector
            jgl::Vector2i* vrs();

            //Return lenght (module/norm) of the vector
            double lenght();

            //Return the distance from the given vector
            double dst(jgl::Vector2i* vec2i);


            //Return dot product
            double dot(jgl::Vector2i* vec2i);

            //Return the cross product.
            //Cross product is not defined in 2d space, anyway we can imagine Z value as 0 
            double crs(jgl::Vector2i* vec2i);

            //Return the angle between two vector in radiants
            double angleRad(jgl::Vector2i* vec2i);
            //Return the angle between two vector in grades
            double angleGrd(jgl::Vector2i* vec2i);


            //Return if the vector is null (lenght = 0)
            bool isNull();

            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector2i* vec2i);

            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector2i* vec2i);

            //Return if the vectors are parallel
            bool isParallel(jgl::Vector2i* vec2i);


            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector2i* vec2i);

            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector2i* vec2i);

            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector2i* vec2i);

            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector2i* vec2i);

            //Rotate vector taking as pivot (0, 0), counter-clockwise, start from x-axis right 
            void rotate(double _rad);

            //Rotate vector around point by vec2i
            void rotateAround(jgl::Vector2i* vec2i, double _rad);

            //Return the vector as string ("x,y")
            std::string* toString();

             static Vector2i xAxis;
             static Vector2i yAxis;
    };   
}

#endif