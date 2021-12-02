#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include "../../JMath.h"

namespace jgl{

    class Vector2d
    {
        private:
            double x, y;

        public:   

            Vector2d();
            Vector2d(double x, double y);
            Vector2d(Vector2d* vec2d);
            Vector2d(std::string* fromString);
            
            double getX();
            double getY();

            void setX(double x);
            void setY(double y);
            void set(Vector2d* vec2d);
            void setAll(double x, double y);

            void addX(double x);
            void addY(double y);
            void add(Vector2d* vec2d);
            void addAll(double x, double y);

            void mulX(double x);
            void mulY(double y);
            void mul(Vector2d* vec2d);
            void mulAll(double x, double y);

            Vector2d* cpy();
    
            //Versor of the vector
            jgl::Vector2d* vrs();

            //Return lenght (module/norm) of the vector
            double lenght();

            //Return the distance from the given vector
            double dst(jgl::Vector2d* vec2d);


            //Return dot product
            double dot(jgl::Vector2d* vec2d);

            //Return the cross product.
            //Cross product is not defined in 2d space, anyway we can imagine Z value as 0 
            double crs(jgl::Vector2d* vec2d);

            //Return the angle between two vector in radiants
            double angleRad(jgl::Vector2d* vec2d);
            //Return the angle between two vector in grades
            double angleGrd(jgl::Vector2d* vec2d);


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
            void rotate(double _rad);

            //Rotate vector around point by vec2d
            void rotateAround(jgl::Vector2d* vec2d, double _rad);

            //Return the vector as string ("x,y")
            std::string* toString();

             static Vector2d xAxis;
             static Vector2d yAxis;

    };   
}

#endif