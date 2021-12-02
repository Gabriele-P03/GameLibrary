#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <string>
#include "../../JMath.h"

namespace jgl{

    class Vector2f
    {
        private:
            float x, y;

        public:   

            Vector2f();
            Vector2f(float x, float y);
            Vector2f(Vector2f* vec2f);
            Vector2f(std::string* fromString);
            
            float getX();
            float getY();

            void setX(float x);
            void setY(float y);
            void set(Vector2f* vec2f);
            void setAll(float x, float y);

            void addX(float x);
            void addY(float y);
            void add(Vector2f* vec2f);
            void addAll(float x, float y);

            void mulX(float x);
            void mulY(float y);
            void mul(Vector2f* vec2f);
            void mulAll(float x, float y);

            Vector2f* cpy();
    
            //Versor of the vector
            jgl::Vector2f* vrs();

            //Return lenght (module/norm) of the vector
            double lenght();

            //Return the distance from the given vector
            double dst(jgl::Vector2f* vec2f);


            //Return dot product
            double dot(jgl::Vector2f* vec2f);

            //Return the cross product.
            //Cross product is not defined in 2d space, anyway we can imagine Z value as 0 
            double crs(jgl::Vector2f* vec2f);

            //Return the angle between two vector in radiants
            double angleRad(jgl::Vector2f* vec2f);
            //Return the angle between two vector in grades
            double angleGrd(jgl::Vector2f* vec2f);


            //Return if the vector is null (lenght = 0)
            bool isNull();

            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector2f* vec2f);

            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector2f* vec2f);

            //Return if the vectors are parallel
            bool isParallel(jgl::Vector2f* vec2f);


            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector2f* vec2f);

            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector2f* vec2f);

            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector2f* vec2f);

            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector2f* vec2f);

            //Rotate vector taking as pivot (0, 0), counter-clockwise, start from x-axis right 
            void rotate(double _rad);

            //Rotate vector around point by vec2f
            void rotateAround(jgl::Vector2f* vec2f, double _rad);

            //Return the vector as string ("x,y")
            std::string* toString();

             static Vector2f xAxis;
             static Vector2f yAxis;
    };   
}

#endif