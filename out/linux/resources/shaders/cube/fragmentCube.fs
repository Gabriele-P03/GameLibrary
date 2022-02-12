#version 330 core

in vec2 outTex;
in vec4 cols;

uniform sampler2D tex;

void main(){

    gl_FragColor = texture(tex, outTex);

}