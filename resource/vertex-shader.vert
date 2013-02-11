#version 150

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;

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

    // Transform every vertex my the camera matrix and projection matrix
    gl_Position = projection * camera * model * vert;
}
