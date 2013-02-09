#version 150

uniform sampler2D tex; // This is the texture

in vec2 fragTexCoord; // This is the texture coordinates

out vec4 finalColor;   // This is the output color for pixels

// The purpose of this fragment shader is to calculate the 
// color of each pixel that is drawn

void main() {
    // set every drawn pixel to white
    finalColor = texture(tex, fragTexCoord);
}