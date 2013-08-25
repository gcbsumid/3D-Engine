#version 330

in vec2 fragTexCoord; // This is the texture coordinates
in vec3 fragNormal;
in vec3 fragVert; 

out vec4 finalColor;   // This is the output color for pixels

void main()
{
    finalColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}