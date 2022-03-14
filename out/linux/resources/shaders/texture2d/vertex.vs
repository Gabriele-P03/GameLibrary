#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
out vec2 outTex;

//Rotation, scaling and translating of the texture
uniform mat4 transform;

/*
    Combined matrix of the camera.
    If this shader is not used during gameplay, i.e. in Main Menu, 'cause there's any camera, 
    you should pass an identity matrix.
*/
uniform mat4 combined;

void main(){

    gl_Position = transform * vec4(pos.xyz, 1.0f);
    outTex = tex;
}
