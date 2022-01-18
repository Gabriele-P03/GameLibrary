#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 outTex;
uniform mat4 transform;

uniform vec4 cols;   //Cols text will be rendered
out vec4 outCols;

void main(){

    gl_Position = transform * vec4(pos.xyz, 1.0f);

    outTex = tex;

    outCols = cols;
}