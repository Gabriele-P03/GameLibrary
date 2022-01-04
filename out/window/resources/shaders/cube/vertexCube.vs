#version 330 core

layout (location = 0) in vec3 pos;
out vec4 cols; //This will be deleted once texture will have been developed

void main(){

    gl_Position = vec4(pos, 1.0f);

    cols = vec4(0.7f, 0.3f, 0.0f, 1.0f);

}