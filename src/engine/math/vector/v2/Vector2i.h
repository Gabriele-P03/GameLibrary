#ifndef VECTOR2I_H
#define VECTOR2I_H

#include <string>
#include "../../JMath.h"
#include "../../matrix/mat3/Matrix3.h"

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



            Vector2i* setX(int x);
            Vector2i* setY(int y);
            Vector2i* set(Vector2i* vec2i);
            Vector2i* setAll(int x, int y);



            Vector2i* addX(int x);
            Vector2i* addY(int y);
            Vector2i* add(Vector2i* vec2i);
            Vector2i* addAll(int x, int y);



            Vector2i* mulX(int x);
            Vector2i* mulY(int y);
            Vector2i* mul(Vector2i* vec2i);
            Vector2i* mulAll(int x, int y);



            Vector2i* cpy();
    


            //Versor of the vector
            jgl::Vector2i* vrs();



            //Return lenght (module/norm) of the vector
            float lenght();



            //Return the distance from the given vector
            float dst(jgl::Vector2i* vec2i);



            //Return dot product
            float dot(jgl::Vector2i* vec2i);



            //Return the cross product.
            //Cross product is not defined in 2d space, anyway we can imagine Z value as 0 
            float crs(jgl::Vector2i* vec2i);



            //Return the angle between two vector in radiants
            float angleRad(jgl::Vector2i* vec2i);
            //Return the angle between two vector in grades
            float angleGrd(jgl::Vector2i* vec2i);



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
            Vector2i* rotate(float _rad);



            //Rotate vector around point by vec2i
            Vector2i* rotateAround(jgl::Vector2i* vec2i, float _rad);



            //Return the vector as string ("x,y")
            std::string* toString();



            static Vector2i xAxis;
            static Vector2i yAxis;
    };   
}

#endif