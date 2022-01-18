#version 330 core

layout (location = 0) in vec3 pos;

out vec4 cols;

void main(){
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);

    cols = vec4(0.0f, 0.5f, 0.5f, 0.0f);
}
