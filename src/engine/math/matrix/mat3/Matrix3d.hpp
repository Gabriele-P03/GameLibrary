#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../vector/v2/Vector2d.h"

namespace jgl{
    
    class Matrix3d{

        private:
            double matrix[3][3];

        public:

            /**
             * Create a new empty matrix
             */ 
            Matrix3d();
            /**
             * Create a new matrix from the given values.
             */ 
            Matrix3d(double x1y1, double x1y2, double x1y3,
                     double x2y1, double x2y2, double x2y3,
                     double x3y1, double x3y2, double x3y3);
            /**
             * Create a new matrix from the given one
             */ 
            Matrix3d(Matrix3d* mat3d);
            /**
             * Create a new rotation matrix from the given yaw (rotation around z-axis)
             */ 
            Matrix3d(double yaw); 
            /**
             * Create a new matrix from the given string.
             * Each box of a row is separated by comma.
             * Each row is separated by semi-colon
             */ 
            Matrix3d(std::string* fromString);



            /**
             * @return a new copy of this matrix
             */ 
            Matrix3d* cpy();



            /**
             * Set this matrix with the given values
             */ 
            Matrix3d* set(double** matrix);
            /**
             * Set this matrix as the given one
             */ 
            Matrix3d* set(Matrix3d* mat3d);
            /**
             * Set matrix[x][y] as value
             */ 
            Matrix3d* set(int x, int y, double value);



            /**
             * @return value stored at the given index
             * @throw error if index is less than 0 or greater than 2
             */ 
            double get(int x, int y);



            /**
             * Add value to all matrix
             * @param value
             */ 
            Matrix3d* addAll(double value);
            /**
             * Add matrix to this one
             * @param mat3d
             */ 
            Matrix3d* add(Matrix3d* mat3d);
            /**
             * Add value to this matrix[x][y]
             * @param x
             * @param y
             * @param value
             */ 
            Matrix3d* add(int x, int y, double value);



            /**
             * Mul value to all matrix.
             * This is scalar multiplication
             * @param value
             */ 
            Matrix3d* mulAll(double value);
            /**
             * Mul matrix to this one
             * @param mat3d
             */ 
            Matrix3d* mul(Matrix3d* mat3d);
            /**
             * Add value to this matrix[x][y]
             * This is scalar multiplication
             * @param x
             * @param y
             * @param value
             */ 
            Matrix3d* mul(int x, int y, double value);



            /**
             *@return determinant of this matrix 
            */
            double det();



            /**
             * Set this matrix as identity
             * @return this matrix
             */ 
            Matrix3d* idt();



            /**
             * Gauss-Jordan method. It applies changes to this matrix, 
             * so you could need to call Matrix3d#cpy() before
             * @return the inverse matrix of this one
             */ 
            Matrix3d* inv();



            /**
             * Multiplies this matrix for a rotation matrix of the given angle, around z-axis
             * @return this matrix
             */ 
            Matrix3d* rotate(double radians);
            /**
             * Set this matrix as a rotation one, with the given angle
             * @return this 
             */ 
            Matrix3d* setToRotation(double radians);
            /**
             * @return the angles represented by this rotation matrix around z-axis
             */ 
            double getRotation();
 


            /**
             * Postmultiplies this matrix with the scale matrix
             * @return this
             */ 
            Matrix3d* scale(double x, double y);
            /**
             * Postmultiplies this matrix with the scale matrix
             * @return this
             */ 
            Matrix3d* scale(Vector2d* vec2d);
            /**
             * Sets this matrix to a scaling one
             * @return this
             */ 
            Matrix3d* setToScaling(double x, double y);
            /**
             * Sets this matrix to a scaling one
             * @return this
             */ 
            Matrix3d* setToScaling(Vector2d* vec2d);
            /**
             * @return vector containing scale of this matrix
             */ 
            Vector2d* getScale();



            /**
             * Postmultiplies this matrix with the translation matrix
             * @return this
             */ 
            Matrix3d* translate(double x, double y);
            /**
             * Postmultiplies this matrix with the translation matrix
             * @return this
             */ 
            Matrix3d* translate(Vector2d* vec2d);
            /**
             * Sets this matrix to a translation one
             * @return this
             */ 
            Matrix3d* setToTranslation(double x, double y);
            /**
             * Sets this matrix to a translation one
             * @return this
             */ 
            Matrix3d* setToTranslation(Vector2d* vec2d);
            /**
             * @return vector containing translate of this matrix
             */ 
            Vector2d* getTranslation();



            /**
             * Returh this matrix as string
             */ 
            std::string* toString();
    };
}

#endif