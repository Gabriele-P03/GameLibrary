#ifndef MATRIX4_H
#define MATRIX4_H

#include <string>
#include "../../JMath.h"
#include "../../vector/quaternion/Quaternion.h"
#include "../../vector/v3/Vector3f.h"

namespace jgl{

    class Quaternion;
    class Vector3f;

    class Matrix4{

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
            void setIdentityMatrix(Matrix4* &idt, int x);

            /**
             * For calculating inverse matrix
             * Nullify the value at x,y substracting itself at all row's value
             *
             * @param idt matrix which will become the inverse 
             * @param x
             * @param y
             * @param row index of the row to be substract from x one
             */
            void substractRow(Matrix4* &idt, int x, int y, int row);


        public:
            float matrix[4][4];
    

            //Create a new matrix
            Matrix4();
            //Create a new matrix from the given values
            Matrix4(float x1y1, float x1y2, float x1y3, float x1y4, 
                    float x2y1, float x2y2, float x2y3, float x2y4, 
                    float x3y1, float x3y2, float x3y3, float x3y4, 
                    float x4y1, float x4y2, float x4y3, float x4y4);
            //Create a new matrix from the given one
            Matrix4(Matrix4* mat4d);
            //Create a new rotation matrix from the given quaternion
            Matrix4(Quaternion* rotation);
            //Create a new matrix from the given rotation, translation and scale. Translation vector must be unit-vector
            Matrix4(Vector3f* position, Quaternion* rotation, jgl::Vector3f* scale);
            //Create a new matrix from the given rotation and translation vector. Scale will be calculated from vector
            Matrix4(Vector3f* position, Quaternion* rotation);
            //Create a new rotation matrix from the given direction vector. As Vector3f#getRotationMatrix(). It uses yAxis as Up 
            Matrix4(Vector3f* direction);
            //Create a new rotation matrix by the given eluer angles
            Matrix4(float yaw, float pitch, float roll);
            //Create a new matrix by the given string as row separated by ';' and col by ','
            Matrix4(std::string* fromString);

            /**
             * @return a copy of this matrix
             */ 
            Matrix4* cpy();



            /**
             * Set this matrix as identity one
             * @return this matrix
             */ 
            Matrix4* idt();



            /**
             * Gauss-Jordan
             * This matrix will be changed. You should call Matrix4#cpy() before
             * @return inverse matrix of this one
             */ 
            Matrix4* inv();



            /**
             * Set all values of this matrix as the given one
             * @param value new value for all matrix
             * @return this matrix
             */ 
            Matrix4* setAll(float value);
            /**
             * Set value[x][y] of this matrix as the given one
             * @param x coord
             * @param y coord
             * @param value new value at x, y
             * @return this matrix
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            Matrix4* set(int x, int y, float value);
            /**
             * Set this matrix as the given one
             * @param mat4d new matrix
             * @return this matrix 
             */ 
            Matrix4* set(Matrix4* mat4d);
            /**
             * Set this matrix from the given array. Its size must be 16
             * @param values float array 
             * @return this matrix
             */ 
            Matrix4* set(float* values);



            /**
             * @param x
             * @param y
             * @return the value at the given x, y
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            float get(int x, int y);



            /**
             * Postmultiplies the given matrix
             * @param mat4d 
             * @return this matrix
             */
            Matrix4* mul(Matrix4* mat4d); 
            /**
             * Scalar mul this matrix for the given value
             * @param value
             * @return this matrix
             */ 
            Matrix4* mulAll(float value);
            /**
             * Scalar mul value at x,y for the given value
             * @param value
             * @return this matrix
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            Matrix4* mul(int x, int y, float value);



            /**
             * Add the given matrix
             * @param mat4d 
             * @return this matrix
             */
            Matrix4* add(Matrix4* mat4d); 
            /**
             * Add value to all matrix
             * @param value
             * @return this matrix
             */ 
            Matrix4* addAll(float value);
            /**
             * Add value at x,y
             * @param value
             * @return this matrix
             * @throw error if x or y are less than 0 or greater than 3
             */ 
            Matrix4* add(int x, int y, float value);



            /**
             * @return determinant of this matrix
             */ 
            float det();



            /**
             * Set this matrix as a rotation one by the given quaternion 
             * @param quaternion
             * @param idt if the matrix must be identified before being rotated
             * @return this matrix
             */ 
            Matrix4* setToRotation(Quaternion* rotation, bool idt);
            /**
             * Set this matrix as a rotation one by the given direction vector
             * @param direction
             * @param up should be 0,1,0 (y-axis)
             * @param idt if the matrix must be identified before being rotated
             * @return this matrix
             */ 
            Matrix4* setToRotation(Vector3f* direction, Vector3f* up, bool idt);
            /**
             * Postmultiplies this matrix by the quaternion given
             * @param rotation
             */
            Matrix4* rotate(Quaternion* rotation); 
            /**
             * Postmultiplies this matrix by direction vector given
             * @param rotation
             */
            Matrix4* rotate(Vector3f* rotation); 
            /**
             * Postmultiplies this matrix by the euler angles given
             * @param yaw
             * @param pitch
             * @param roll
             */
            Matrix4* rotate(float yaw, float pitch, float roll); 
            /**
             * @return the direction vector which this rotation matrix represents
             */
            Vector3f* getRotation(); 


            /**
             * Translate this matrix with the given values
             * @param x
             * @param y
             * @param z
             * @return this matrix
             */ 
            Matrix4* translate(float x, float y, float z);
            /**
             * Translate this matrix with the given vector
             * @param scale
             * @return this matrix
             */ 
            Matrix4* translate(Vector3f* position);
            /**
             * Set to translation this matrix with the given values
             * @param x
             * @param y
             * @param z
             * @param idt if the matrix must be identified before being rotated
             * @return this matrix
             */ 
            Matrix4* setToTranslation(float x, float y, float z, bool idt);
            /**
             * Set this matrix as a translating one by the given position vector
             * @param position position vector
             * @param idt if the matrix must be identified before being rotated
             * @return this matrix
             */
            Matrix4* setToTranslation(Vector3f* position, bool idt);
            /**
             * @return the position vector which this matrix represents 
             */ 
            Vector3f* getTranslation(); 


            /**
             * Scale this matrix with the given vector
             * @param x
             * @param y
             * @param z
             * @return this matrix
             */ 
            Matrix4* scale(float x, float y, float z);
            /**
             * Scale this matrix with the given values
             * @param scale
             * @return this matrix
             */ 
            Matrix4* scale(Vector3f* scale);
            /**
             * Set this matrix as a scaling one by the given scale vector
             * @param x
             * @param y
             * @param z
             * @param idt if the matrix must be identified before being rotated
             * @return this matrix
             */ 
            Matrix4* setToScale(float x, float y, float z, bool idt);
            /**
             * Set this matrix as a scaling one by the given scale vector
             * @param scale scale vector
             * @param idt if the matrix must be identified before being rotated
             * @return this matrix
             */ 
            Matrix4* setToScale(Vector3f* scale, bool idt);
            /**
             * @return the scale vector this matrix represent
             */ 
            Vector3f* getScale();


            /**
             * @return the quaternion which represents the rotation of this rotation matrix 
             */
            Quaternion* getQuaternion(); 



            /**
             * @return a string representing this matrix separating rows by ';' and cols by ','
             */  
            std::string* toString();


            //A static identity matrix
            static Matrix4* matIdt;
    };      
}

#endif