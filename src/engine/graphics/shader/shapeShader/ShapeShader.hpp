/**
 * A Shape Shader instance provide rendering methods for draw on screen shapes as:
 * circle, line, rectangular, quad and triangle
 * 
 * These shape's vertices are already declaread and taken once you have passed your SHAPE_TYPE needed.
 * Anyway you can set your own vertices if you wanna draw an another type of shape
 * 
 * You can also draw the shape with the color you wanna
 * 
 * As you can see, the vertex code and fragment code which ShapeShader needs 
 * is very similar to TextShader's one, in fact it uses that.
 * But it neither inheritance it nor TextureShader - as it doesn't render any texture -.
 * 
 * @author Gabriele-P03
 */ 

#ifndef SHAPESHADER_JPL_HPP
#define SHAPESHADER_JPL_HPP

#include "../Shader.h"
#include "../../../math/matrix/mat4/Matrix4.h"

namespace jpl{

    class ShapeShader : public Shader{
        
        typedef unsigned short SHAPE_TYPE;

        private:

            bool working;

            SHAPE_TYPE shape_type;
            
            jgl::Matrix4* transform;

            /**
             * @param shape_type
             * @param size of the array which will be returned
             * @return float array which stores vertices of shape
             */ 
            void getShapeVertices(SHAPE_TYPE shape_type, float* &vertices, unsigned int &_sizeVertices, unsigned int* &indices, unsigned int &_sizeIndices);

            /**
             * Check if ShapeShader#begin() has been called before any draw calling
             */ 
            void checkBeginCall(SHAPE_TYPE shape_type);

            /**
             * Bind shader buffers and draw stuff
             * It is not called by ShapeShader#drawLine() 'cause it needs to be rendered via glDrawArray()
             */ 
            inline void bindAndDraw(float* colors);
            
        public:

            static const SHAPE_TYPE SHAPE_LINE = 0;
            static const SHAPE_TYPE SHAPE_TRIANGLE = 1;
            static const SHAPE_TYPE SHAPE_QUAD = 2;
            static const SHAPE_TYPE SHAPE_CIRCLE = 3;

            ShapeShader();

            /**
             * @return shape currently using
             */
            SHAPE_TYPE getShapeType();

            /**
             * Make available shader program of ShapeRender
             * It uses SHAPE_QUAD as default
             */ 
            void begin();
            /**
             * Make available shader program of ShapeRender
             * @param shape_type 
             */
            void begin(SHAPE_TYPE shape_type); 

            /**
             * Disable shader program
             */ 
            void end();

            /**
             * Draw a line horizzontally on the window
             * @param x 
             * @param y
             * @param length
             */ 
            void drawLine(int x, int y, float length, float* colors);

            /**
             * Draw a quad begin the bottom-left corner at x,y
             * @param x
             * @param y
             * @param length of each side
             * @param colors 4 float array which stores colors values as RGBA
             */ 
            void drawQuad(int x, int y, float length, float* colors);
            /**
             * Draw an equilater triangle begin the bottom-left corner at x,y
             * @param x
             * @param y
             * @param length of each side
             * @param colors 4 float array which stores colors values as RGBA
             */ 
            void drawTriangle(int x, int y, float length, float* colors);
    };
}

#endif