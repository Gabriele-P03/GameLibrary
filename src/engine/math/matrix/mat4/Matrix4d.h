#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <string>
#include "../../JMath.h"
#include "../../vector/quaternion/Quaternion.h"
#include "../../vector/v3/Vector3d.h"

namespace jgl{

    class Vector3d;

    class Matrix4d{

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
            void setIdentityMatrix(Matrix4d* &idt, int x);

            /**
             * For calculating inverse matrix
             * Nullify the value at x,y substracting itself at all row's value
             *
             * @param idt matrix which will become the inverse 
             * @param x
             * @param y
             * @param row index of the row to be substract from x one
             */
            void substractRow(Matrix4d* &idt, int x, int y, int row);


        public:
            double matrix[4][4];
    

            //Create a new matrix
            Matrix4d();
            //Create a new matrix from the given values
            Matrix4d(double x1y1, double x1y2, double x1y3, double x1y4, 
                    double x2y1, double x2y2, double x2y3, double x2y4, 
                    double x3y1, double x3y2, double x3y3, double x3y4, 
                    double x4y1, double x4y2, double x4y3, double x4y4);
            //Create a new matrix from the given one
            Matrix4d(Matrix4d* mat4d);
            //Create a new rotation matrix from the given quaternion
            Matrix4d(Quaternion* rotation);
            //Create a new matrix from the given rotation, translation and scale
            Matrix4d(Vector3d* position, Quaternion* rotation, Vector3d* scale);



            /**
             * @return a copy of this matrix
             */ 
            Matrix4d* cpy();



            /**
             * Set this matrix as identity one
             * @return this matrix
             */ 
            Matrix4d* idt();



            /**
             * Gauss-Jordan
             * This matrix will be changed. You should call Matrix4d#cpy() before
             * @return inverse matrix of this one
             */ 
            Matrix4d* inv();



            /**
             * Set all values of this matrix as the given one
             * @param value new value for all matrix
             * @return this matrix
             */ 
            Matrix4d* setAll(double value);
            /**
             * Set value[x][y] of this matrix as the given one
             * @param x coord
             * @param y coord
             * @param value new value at x, y
             * @return this matrix
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            Matrix4d* set(int x, int y, double value);
            /**
             * Set this matrix as the given one
             * @param mat4d new matrix
             * @return this matrix 
             */ 
            Matrix4d* set(Matrix4d* mat4d);
            /**
             * Set this matrix from the given array. Its size must be 16
             * @param values double array 
             * @return this matrix
             */ 
            Matrix4d* set(double* values);



            /**
             * @param x
             * @param y
             * @return the value at the given x, y
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            double get(int x, int y);



            /**
             * Postmultiplies the given matrix
             * @param mat4d 
             * @return this matrix
             */
            Matrix4d* mul(Matrix4d* mat4d); 
            /**
             * Scalar mul this matrix for the given value
             * @param value
             * @return this matrix
             */ 
            Matrix4d* mulAll(double value);
            /**
             * Scalar mul value at x,y for the given value
             * @param value
             * @return this matrix
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            Matrix4d* mul(int x, int y, double value);



            /**
             * Add the given matrix
             * @param mat4d 
             * @return this matrix
             */
            Matrix4d* add(Matrix4d* mat4d); 
            /**
             * Add value to all matrix
             * @param value
             * @return this matrix
             */ 
            Matrix4d* addAll(double value);
            /**
             * Add value at x,y
             * @param value
             * @return this matrix
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            Matrix4d* add(int x, int y, double value);



            /**
             * @return determinant of this matrix
             */ 
            double det();
    };
}

#endif