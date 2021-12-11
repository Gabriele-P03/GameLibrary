#ifndef Vector2F_H
#define Vector2F_H

#include <string>
#include "../../JMath.h"
#include "../../matrix/mat3/Matrix3d.h"

namespace jgl{

    class Matrix3d;

    class Vector2f
    {
        private:
            float x, y;

        public:   

            /**
             * Create a vector 0, 0
             */ 
            Vector2f();
            /**
             * Create a new vector with the given value
             * @param x
             * @param y
             */ 
            Vector2f(float x, float y);
            /**
             * Create a new vector as the given one
             * @param vec2f
             */ 
            Vector2f(Vector2f* vec2f);
            /**
             * Create a new vector from the given string "x,y"
             * @param fromString
             */ 
            Vector2f(std::string* fromString);
            


            float getX();
            float getY();



            Vector2f* setX(float x);
            Vector2f* setY(float y);
            Vector2f* set(Vector2f* vec2f);
            Vector2f* setAll(float x, float y);



            Vector2f* addX(float x);
            Vector2f* addY(float y);
            Vector2f* add(Vector2f* vec2f);
            Vector2f* addAll(float x, float y);



            Vector2f* mulX(float x);
            Vector2f* mulY(float y);
            Vector2f* mul(Vector2f* vec2f);
            Vector2f* mulAll(float x, float y);



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
            Vector2f* rotate(double _rad);



            //Rotate vector around pofloat by vec2f
            Vector2f* rotateAround(jgl::Vector2f* vec2f, double _rad);



            //Return the vector as string ("x,y")
            std::string* toString();



            //Get the rotation matrix of this vector
            Matrix3d* getRotationMatrix();
            //Get the translation matrix of this vector
            Matrix3d* getTranslationMatrix();
            //Get the scaling matrix of this vector
            Matrix3d* getScalingMatrix();



            static Vector2f xAxis;
            static Vector2f yAxis;
    };   
}

#endif