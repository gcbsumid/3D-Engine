#version 150

uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNormal;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;

// Note: All vertex shaders must set a gl_Position

void main() {
    // Pass the texture coordinate straight through to 
    // the fragment shader.
    fragTexCoord = vertTexCoord;
    fragNormal = vertNormal;
    fragVert = vert;

    // Transform every vertex my the camera matrix and projection matrix
    gl_Position = camera * model * vec4(vert, 1);
}
