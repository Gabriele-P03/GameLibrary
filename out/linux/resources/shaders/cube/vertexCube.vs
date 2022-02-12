#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 transform;
uniform mat4 combined;

out vec2 outTex;
out vec4 cols; //This will be deleted once texture will have been developed

void main(){

    gl_Position = combined * transform * vec4(pos, 1.0f);

    outTex = tex;
    cols = vec4(0.7f, 0.3f, 0.0f, 1.0f);

}