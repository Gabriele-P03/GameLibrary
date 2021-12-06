#ifndef Vector2D_H
#define Vector2D_H

#include <string>
#include "../../JMath.h"
#include "../../matrix/mat3/Matrix3d.h"

namespace jgl{

    class Matrix3d;

    class Vector2d
    {
        private:
            double x, y;

        public:   

            Vector2d();
            Vector2d(double x, double y);
            Vector2d(Vector2d* vec2d);
            Vector2d(std::string* fromString);
            Vector2d(Matrix3d* mat3d);
            


            double getX();
            double getY();



            Vector2d* setX(double x);
            Vector2d* setY(double y);
            Vector2d* set(Vector2d* vec2d);
            Vector2d* setAll(double x, double y);



            Vector2d* addX(double x);
            Vector2d* addY(double y);
            Vector2d* add(Vector2d* vec2d);
            Vector2d* addAll(double x, double y);



            Vector2d* mulX(double x);
            Vector2d* mulY(double y);
            Vector2d* mul(Vector2d* vec2d);
            Vector2d* mulAll(double x, double y);



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
            Vector2d* rotate(double _rad);



            //Rotate vector around podouble by vec2d
            Vector2d* rotateAround(jgl::Vector2d* vec2d, double _rad);



            //Return the vector as string ("x,y")
            std::string* toString();



            //Get the transformation matrix of this vector, containing only rotation and translation
            Matrix3d* getTransformationMatrix();
            //Get the rotation matrix of this vector
            Matrix3d* getRotationMatrix();
            //Get the translation matrix of this vector
            Matrix3d* getTranslationMatrix();
            //Get the scaling matrix of this vector
            Matrix3d* getScalingMatrix();



            static Vector2d xAxis;
            static Vector2d yAxis;
    };   
}

#endif