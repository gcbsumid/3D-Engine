#version 150

uniform mat4 model;
uniform sampler2D tex; // This is the texture

uniform struct Light {
    vec3 position;
    vec3 intensities;   // color of the light
} light;

in vec2 fragTexCoord; // This is the texture coordinates
in vec3 fragNormal;
in vec3 fragVert; 

out vec4 finalColor;   // This is the output color for pixels

// The purpose of this fragment shader is to calculate the 
// color of each pixel that is drawn

void main() {
    // calculate the normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);

    // calculate the location of this fragment in world coords
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));

    // calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = light.position - fragPosition;

    // calculate the cosine of the angle of inscidence (brightness)
    float brightness = dot(surfaceToLight, normal) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    // calculate the final colour of the pixel based on:
    // 1. brightness, 
    // 2. light.intensities
    // 3. texture(tex, fragTexCoord)
    finalColor = brightness * vec4(light.intensities, 1) * texture(tex, fragTexCoord);
}