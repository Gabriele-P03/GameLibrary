#version 330 core 

in vec2 outTex;
in vec3 cols;

uniform sampler2D texture1; 

void main(){

    gl_FragColor = texture(texture1, outTex);// * vec4(1.0f, 0.0f, 1.0f, 0.5f);
    
}