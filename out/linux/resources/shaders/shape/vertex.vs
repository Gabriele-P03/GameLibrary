#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 transform;

uniform vec4 cols;   //Cols text will be rendered
out vec4 outCols;

uniform float circle;
out float isCircular;

void main(){

    gl_Position = transform * vec4(pos.xyz, 1.0f);
    isCircular = circle; 
    outCols = cols;
}