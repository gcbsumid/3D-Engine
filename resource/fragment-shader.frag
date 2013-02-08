#version 150

out vec4 finalColor; 

// The purpose of this fragment shader is to calculate the 
// color of each pixel that is drawn

void main() {
    // set every drawn pixel to white
    finalColor = vec4(1.0, 1.0, 1.0, 1.0);
}