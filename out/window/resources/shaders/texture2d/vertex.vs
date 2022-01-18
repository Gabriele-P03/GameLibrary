#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
out vec2 outTex;

void main(){
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
    outTex = tex;
}
