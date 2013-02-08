#version 150

in vec4 vert;

// The purpose of the vertex shader is to transform points
// into different points.

void main() {
    // does not alter vertices at all
    // Note: All vertex shaders must set a gl_Position
    gl_Position = vert;
}
