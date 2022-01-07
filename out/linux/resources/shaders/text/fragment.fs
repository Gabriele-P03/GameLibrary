#version 330 core

in vec2 outTex;
in vec4 outCols;

uniform sampler2D texture1; 

void main(){

    gl_FragColor = texture2D(texture1, outTex) * outCols;
}