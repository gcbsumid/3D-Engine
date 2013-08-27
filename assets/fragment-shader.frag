#version 330

in vec2 fragTexCoord; // This is the texture coordinates
in vec3 fragNormal;
in vec3 fragVert; 

out vec4 finalColor;   // This is the output color for pixels

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;
const int MAX_DIRECTIONAL_LIGHTS = 3;

/*************************************************************************
 * Definitions:                                                          *
 *      Diffuse - Only show vertices whose angle between its normal and  *
 *                surface-to-light vectors are accute or perpendicular   *
 *      Ambient - Minimum brightness (so the parts of the model that the *
 *                light doesn't touch is also seen)                      *
 *      Specular - Intense white reflected light. Makes the model shiny  *
 *      Attenuation - loss of light intensity over distance. The greater *
 *                    the distance, the lower the intensity              *
 *      Half Vector - Vector bisecting the light direction and viewing   *
 *                    direction.                                         *
 ************************************************************************/

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct BaseLight {
    vec3 color;   // intensities of the light
    vec4 diffuse;
    float ambient;
    float specular; 
    vec3 halfvector;
};

// Light Types
struct DirectionalLight {
    BaseLight base;
    vec3 direction;
};

struct PointLight {
    BaseLight base;
    vec3 position;
    Attenuation attenuation;  
};

struct SpotLight {
    PointLight Base;
    vec3 direction;
    float cutoff; // angle cutoff between light-to-pixel vector and light-direction vector
    float exponent;
};

uniform int numPointLights;
uniform int numSpotLights;
uniform int numDirectionalLights;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

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
    vec3 fragNormalInWorld = normalize(transpose(inverse(mat3(model))) * fragNormal);

    vec3 surfacePos = vec3(model * vec4(fragVert, 1));
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
}

vec3 CalculateDirectionalLight(const in int i,
                               const in vec3 normal,
                               inout vec4 ambient,
                               inout vec4 diffuse,
                               inout vec4 specular) 
{
    float normalDotLightDirection;
    float normalDotHalfVector;
    float power;

    normalDotLightDirection = max(0.0, dot(normal, normalize(directionalLights[i].direction)));
    normalDotHalfVector = max(0.0, dot(normal, normalize(directionalLights[i].base.halfvector)));

    if (normalDotLightDirection == 0.0) 
        power = 0.0;
    else 
        power = pow(normalDotHalfVector, material.shininess);

    ambient += directionalLights[i].ambient;
    diffuse += directionalLights[i].diffuse * normalDotLightDirection;
    specular += directionalLights[i].specular * power;
} 

vec3 CalculatePointLight(const in int i,
                         const in vec3 eye,
                         const in vec3 eyeCoordinatePosition,
                         const in vec3 normal,
                         inout vec4 ambient,
                         inout vec4 diffuse,
                         inout vec4 specular)
{
    float normalDotLightDirection; 
    float normalDotHalfVector;
    float power;
    float attenuation;      // Computed attenuation factor
    float dist;                // Distance from surface to light position
    vec3 surfaceToLight;    // direction from surface to light position

    surfaceToLight = vec3(pointLights[i].position - eyeCoordinatePosition);
    dist = length(surfaceToLight);
    surfaceToLight = normalize(surfaceToLight);

    attenuation = 1.0 / (pointLights[i].attenuation.constant +
                         pointLights[i].attneuation.linear * dist +
                         pointLights[i].attenuation.quadratic * dist * dist) ;

    pointLights[i].halfvector = normalize(surfaceToLight + eye);

    normalDotLightDirection = max(0.0, dot(normalDotLightDirection, normal));
    normalDotHalfVector = max(0.0, dot(pointlights.halfvector, normal));

    if (normalDotLightDirection == 0.0) 
        power = 0.0;
    else 
        power = pow (normalDotHalfVector, material.shininess);

    ambient += pointlights[i].ambient * attenuation;
    diffuse += pointlights[i].diffuse * attenuation;
    specular += pointlights[i].specular * pf * attenuation;
}

vec3 CalculateSpotLight(const in int i,
                         const in vec3 eye,
                         const in vec3 eyeCoordinatePosition,
                         const in vec3 normal,
                         inout vec4 ambient,
                         inout vec4 diffuse,
                         inout vec4 specular)
{
    float normalDotLightDirection;
    float normalDotHalfVector;
    float power;
    float attenuation;
    float dist;
    vec3 surfaceToLight;
    float spotAttenuation;

    surfaceToLight = vec3(spotLights[i].position - eyeCoordinatePosition);
    dist = length(surfaceToLight);
    surfaceToLight = normalize(surfaceToLight);

    attenuation = 1.0 / (spotLights[i].attenuation.constant +
                         spotLights[i].attneuation.linear * dist +
                         spotLights[i].attenuation.quadratic * dist * dist) ;

    float surfaceToLightDotDirection = dot(-surfaceToLight, normalize(spotLights[i].direction));
    if (surfaceToLightDotDirection < spotLights[i].cutoff) {
        spotAttenuation = 0.0;
    } else {
        spotAttenuation = pow(surfaceToLightDotDirection, spotLights[i].exponent);
    }

    attenuation = attenuation * spotAttenuation;

    spotLights[i].halfvector = normalize(surfaceToLight + eye);

    normalDotLightDirection = max(0.0, dot(normalDotLightDirection, normal));
    normalDotHalfVector = max(0.0, dot(pointlights.halfvector, normal));

    if (normalDotLightDirection == 0.0) {
        power = 0.0;
    } else {
        power = pow(normalDotHalfVector, material.shininess);
    }

    ambient += pointlights[i].ambient * attenuation;
    diffuse += pointlights[i].diffuse * attenuation;
    specular += pointlights[i].specular * pf * attenuation;    
}