#ifndef Vector2D_H
#define Vector2D_H

#include <string>
#include "../../JMath.h"
#include "../../matrix/mat3/Matrix3.h"

namespace jgl{

    class Matrix3;

    class Vector2d
    {
        private:
            float x, y;

        public:   

            /**
             * Create a vector 0, 0
             */ 
            Vector2d();
            /**
             * Create a new vector with the given value
             * @param x
             * @param y
             */ 
            Vector2d(float x, float y);
            /**
             * Create a new vector as the given one
             * @param vec2d
             */ 
            Vector2d(Vector2d* vec2f);
            /**
             * Create a new vector from the given string "x,y"
             * @param fromString
             */ 
            Vector2d(std::string* fromString);
            


            float getX();
            float getY();



            Vector2d* setX(float x);
            Vector2d* setY(float y);
            Vector2d* set(Vector2d* vec2d);
            Vector2d* setAll(float x, float y);



            Vector2d* addX(float x);
            Vector2d* addY(float y);
            Vector2d* add(Vector2d* vec2d);
            Vector2d* addAll(float x, float y);



            Vector2d* mulX(float x);
            Vector2d* mulY(float y);
            Vector2d* mul(Vector2d* vec2d);
            Vector2d* mulAll(float x, float y);



            Vector2d* cpy();
    


            //Versor of the vector
            jgl::Vector2d* vrs();



            //Return lenght (module/norm) of the vector
            float lenght();



            //Return the distance from the given vector
            float dst(jgl::Vector2d* vec2d);



            //Return dot product
            float dot(jgl::Vector2d* vec2d);



            //Return the cross product.
            //Cross product is not defined in 2d space, anyway we can imagine Z value as 0 
            float crs(jgl::Vector2d* vec2d);



            //Return the angle between two vector in radiants
            float angleRad(jgl::Vector2d* vec2d);
            //Return the angle between two vector in grades
            float angleGrd(jgl::Vector2d* vec2d);



            //Return if the vector is null (lenght = 0)
            bool isNull();



            //Return if the vectors are equal (parallel and lenght)
            bool equals(jgl::Vector2d* vec2d);



            //Return if the vectors are perpendicular
            bool isPerpendicular(jgl::Vector2d* vec2d);



            //Return if the vectors are parallel
            bool isParallel(jgl::Vector2d* vec2d);



            //Return if the vectors has the same directions
            bool sameDirection(jgl::Vector2d* vec2d);



            //Return if the vectors has opposite direction
            bool oppositeDirection(jgl::Vector2d* vec2d);



            //Return if the vectors form an acute angle
            //If the dot product is positive, they form acute one
            bool acuteAngle(jgl::Vector2d* vec2d);



            //Return if the vectors form an obtuse angle
            //If the dot product is negative, they form acute one
            bool obtuseAngle(jgl::Vector2d* vec2d);



            //Rotate vector taking as pivot (0, 0), counter-clockwise, start from x-axis right 
            Vector2d* rotate(float _rad);



            //Rotate vector around pofloat by vec2d
            Vector2d* rotateAround(jgl::Vector2d* vec2d, float _rad);



            //Return the vector as string ("x,y")
            std::string* toString();



            //Get the rotation matrix of this vector
            Matrix3* getRotationMatrix();
            //Get the translation matrix of this vector
            Matrix3* getTranslationMatrix();
            //Get the scaling matrix of this vector
            Matrix3* getScalingMatrix();



            static Vector2d xAxis;
            static Vector2d yAxis;
    };   
}

#endif