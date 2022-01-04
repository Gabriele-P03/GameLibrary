#ifndef MATRIX3_H
#define MATRIX3_H

#include <iostream>
#include <string>
#include "../../JMath.h"
#include "../../vector/v2/Vector2f.h"

namespace jgl{
    
    class Vector2d;

    class Matrix3{

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
            void setIdentityMatrix(Matrix3* &idt, int x);

            /**
             * For calculating inverse matrix
             * Nullify the value at x,y substracting itself at all row's value
             *
             * @param idt matrix which will become the inverse 
             * @param x
             * @param y
             * @param row index of the row to be substract from x one
             */
            void substractRow(Matrix3* &idt, int x, int y, int row);

        public:
            float matrix[3][3];

            /**
             * Create a new empty matrix
             */ 
            Matrix3();
            /**
             * Create a new matrix from the given array. Its size must be 9
             */ 
            Matrix3(float* values);
            /**
             * Create a new matrix from the given values.
             */ 
            Matrix3(float x1y1, float x1y2, float x1y3,
                     float x2y1, float x2y2, float x2y3,
                     float x3y1, float x3y2, float x3y3);
            /**
             * Create a new matrix from the given one
             */ 
            Matrix3(Matrix3* mat3d);
            /**
             * Create a new rotation matrix from the given yaw (rotation around z-axis)
             */ 
            Matrix3(float yaw); 
            /**
             * Create a new transformation matrix which represents the given postition, rotation around z-axis and scale.
             * 
             * If your position vector is not unit-vector, you should use Matrix3#Matrix3(float yaw, Vector3d* position) else
             * you may pass as position the versor of your postion vector and as scale its length
             * @param yaw
             * @param position
             * @param scale
             */
            Matrix3(float yaw, Vector2d* position, float scale);
            /**
             * Create a new transformation matrix which represents the given position and rotation around z-axis.
             * Scale will be calculated by the given position, then you should not pass a unit-vector
             * @param yaw
             * @param position
             */
            Matrix3(float yaw, Vector2d* position);  
            /**
             * Create a new matrix from the given string.
             * Each box of a row is separated by comma.
             * Each row is separated by semi-colon
             */ 
            Matrix3(std::string* fromString);



            /**
             * @return a new copy of this matrix
             */ 
            Matrix3* cpy();


            /**
             * Set this matrix as the given array. Its size must be 16
             * @param values float array
             * @return this matrix
             */ 
            Matrix3* set(float* values);
            /**
             * Set this matrix as the given one
             * @param mat3d matrix
             * @return this matrix
             */ 
            Matrix3* set(Matrix3* mat3d);
            /**
             * Set matrix[x][y] as value
             * @param x coord
             * @param y coord
             * @param value new value at x, y
             * @return this matrix
             * @throw error if index is less than 0 or greater than 2
             */ 
            Matrix3* set(int x, int y, float value);
            /**
             * Set all values as the given one
             * @param value new value to be set at all matrix 
             * @return this matrix
             */ 
            Matrix3* setAll(float value);



            /**
             * @param x
             * @param y
             * @return value stored at the given index
             * @throw error if index is less than 0 or greater than 2
             */ 
            float get(int x, int y);



            /**
             * Add value to all matrix
             * @param value
             * @return this matrix
             */ 
            Matrix3* addAll(float value);
            /**
             * Add matrix to this one
             * @param mat3d matrix
             * @return this matrix
             */ 
            Matrix3* add(Matrix3* mat3d);
            /**
             * Add value to this matrix[x][y]
             * @param x
             * @param y
             * @param value
             * @return this matrix
             * @throw error if index is less than 0 or greater than 2
             */ 
            Matrix3* add(int x, int y, float value);



            /**
             * Mul value to all matrix.
             * This is scalar multiplication
             * @param value
             * @return this matrix
             */ 
            Matrix3* mulAll(float value);
            /**
             * Mul matrix to this one
             * @param mat3d
             * @return this matrix
             */ 
            Matrix3* mul(Matrix3* mat3d);
            /**
             * Add value to this matrix[x][y]
             * This is scalar multiplication
             * @param x coord
             * @param y coord
             * @param value
             * @return this matrix
             */ 
            Matrix3* mul(int x, int y, float value);



            /**
             *@return determinant of this matrix 
            */
            float det();



            /**
             * Set this matrix as identity
             * @return this matrix
             */ 
            Matrix3* idt();



            /**
             * Gauss-Jordan method. It applies changes to this matrix, 
             * so you could need to call Matrix3#cpy() before
             * @return the inverse matrix of this one
             */ 
            Matrix3* inv();



            /**
             * Multiplies this matrix for a rotation matrix of the given angle, around z-axis
             * @return this matrix
             */ 
            Matrix3* rotate(float radians);
            /**
             * Set this matrix as a rotation one, with the given angle
             * @return this 
             */ 
            Matrix3* setToRotation(float radians);
            /**
             * @return the angles represented by this rotation matrix around z-axis
             */ 
            float getRotation();
 


            /**
             * Postmultiplies this matrix with the scale matrix
             * @return this
             */ 
            Matrix3* scale(float x, float y);
            /**
             * Postmultiplies this matrix with the scale matrix
             * @return this
             */ 
            Matrix3* scale(Vector2d* vec2d);
            /**
             * Sets this matrix to a scaling one
             * @return this
             */ 
            Matrix3* setToScaling(float x, float y);
            /**
             * Sets this matrix to a scaling one
             * @return this
             */ 
            Matrix3* setToScaling(Vector2d* vec2d);
            /**
             * @return scale of the vector which matrix represents
             */ 
            float getScale();



            /**
             * Postmultiplies this matrix with the translation matrix
             * @return this
             */ 
            Matrix3* translate(float x, float y);
            /**
             * Postmultiplies this matrix with the translation matrix
             * @return this
             */ 
            Matrix3* translate(Vector2d* vec2d);
            /**
             * Sets this matrix to a translation one
             * @return this
             */ 
            Matrix3* setToTranslation(float x, float y);
            /**
             * Sets this matrix to a translation one
             * @return this
             */ 
            Matrix3* setToTranslation(Vector2d* vec2d);
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