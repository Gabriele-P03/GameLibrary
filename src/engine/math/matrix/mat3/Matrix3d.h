#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../vector/v2/Vector2d.h"

namespace jgl{
    
    class Vector2d;

    class Matrix3d{

        private:

            /**
             * For calculating inverse matrix
             * On the main diagonal values must be 1. This method checks if tha value at x,x is 1, else it will divide
             * all row by value at x, x. 
             * 
             * @param mat matrix to be computing
             * @param idt matrix which will become the inverse one
             * @param x coord for identify value on main diagonal
             */ 
            void setIdentityMatrix(Matrix3d* &idt, int x);

            /**
             * For calculating inverse matrix
             * Nullify the value at x,y substracting itself at all row's value
             *
             * @param idt matrix which will become the inverse 
             * @param x
             * @param y
             * @param row index of the row to be substract from x one
             */
            void substractRow(Matrix3d* &idt, int x, int y, int row);

        public:
            double matrix[3][3];

            /**
             * Create a new empty matrix
             */ 
            Matrix3d();
            /**
             * Create a new matrix from the given array. Its size must be 9
             */ 
            Matrix3d(double* values);
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
             * Create a new transformation matrix which represents the given postition, rotation around z-axis and scale.
             * 
             * If your position vector is not unit-vector, you should use Matrix3d#Matrix3d(double yaw, Vector3d* position) else
             * you may pass as position the versor of your postion vector and as scale its length
             * @param yaw
             * @param position
             * @param scale
             */
            Matrix3d(double yaw, Vector2d* position, double scale);
            /**
             * Create a new transformation matrix which represents the given position and rotation around z-axis.
             * Scale will be calculated by the given position, then you should not pass a unit-vector
             * @param yaw
             * @param position
             */
            Matrix3d(double yaw, Vector2d* position);  
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
             * Set this matrix as the given array. Its size must be 16
             * @param values double array
             * @return this matrix
             */ 
            Matrix3d* set(double* values);
            /**
             * Set this matrix as the given one
             * @param mat3d matrix
             * @return this matrix
             */ 
            Matrix3d* set(Matrix3d* mat3d);
            /**
             * Set matrix[x][y] as value
             * @param x coord
             * @param y coord
             * @param value new value at x, y
             * @return this matrix
             * @throw error if index is less than 0 or greater than 2
             */ 
            Matrix3d* set(int x, int y, double value);
            /**
             * Set all values as the given one
             * @param value new value to be set at all matrix 
             * @return this matrix
             */ 
            Matrix3d* setAll(double value);



            /**
             * @param x
             * @param y
             * @return value stored at the given index
             * @throw error if index is less than 0 or greater than 2
             */ 
            double get(int x, int y);



            /**
             * Add value to all matrix
             * @param value
             * @return this matrix
             */ 
            Matrix3d* addAll(double value);
            /**
             * Add matrix to this one
             * @param mat3d matrix
             * @return this matrix
             */ 
            Matrix3d* add(Matrix3d* mat3d);
            /**
             * Add value to this matrix[x][y]
             * @param x
             * @param y
             * @param value
             * @return this matrix
             * @throw error if index is less than 0 or greater than 2
             */ 
            Matrix3d* add(int x, int y, double value);



            /**
             * Mul value to all matrix.
             * This is scalar multiplication
             * @param value
             * @return this matrix
             */ 
            Matrix3d* mulAll(double value);
            /**
             * Mul matrix to this one
             * @param mat3d
             * @return this matrix
             */ 
            Matrix3d* mul(Matrix3d* mat3d);
            /**
             * Add value to this matrix[x][y]
             * This is scalar multiplication
             * @param x coord
             * @param y coord
             * @param value
             * @return this matrix
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
             * @return scale of the vector which matrix represents
             */ 
            double getScale();



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