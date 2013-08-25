#version 330

in vec2 fragTexCoord; // This is the texture coordinates
in vec3 fragNormal;
in vec3 fragVert; 

out vec4 finalColor;   // This is the output color for pixels

uniform struct Light {
    vec3 position;
    vec3 intensities;   // color of the light
    float ambientCoefficient;
    float attenuation;
} light;

uniform struct Material {
    sampler2D tex; // This is the texture
    float shininess;
    vec3 specularColor;
} material;

uniform mat4 model;
uniform vec3 cameraPosition;

// The purpose of this fragment shader is to calculate the 
// color of each pixel that is drawn

void main() {
    vec3 fragNormalInWorld = normalize(fragNormal);

    vec3 surfacePos = fragVert;
    vec4 surfaceColor = texture(material.tex, fragTexCoord);
    vec3 surfaceToLight = normalize(light.position - surfacePos);

    // calulate for the diffuse
    float diffuseCoefficient = max(0.0, dot(fragNormalInWorld, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;

    // Calculate the ambience
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    // Calculate the specular
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0) {
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, fragNormalInWorld))), material.shininess);
    }
    vec3 specular = specularCoefficient * material.specularColor * light.intensities;

    // Calculate the light attenuation (as light source fades)
    float distanceToLight = length(light.position - surfacePos);
    float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

    // Calculate the color at that point
    vec3 linearColor = ambient + attenuation*(diffuse + specular);

    vec3 gamma = vec3(1.0/2.2);
    finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);
    // finalColor = vec4(1.0, 1.0, 1.0, 1.0);
}