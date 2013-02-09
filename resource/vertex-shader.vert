#version 150

in vec4 vert;
in vec2 vertTexCoord;

out vec2 fragTexCoord;

// The purpose of the vertex shader is to transform points
// into different points.
// Note: All vertex shaders must set a gl_Position

void main() {
    // Pass the texture coordinate straight through to 
    // the fragment shader.
    fragTexCoord = vertTexCoord;

    gl_Position = vert;
}
