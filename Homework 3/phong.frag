#version 330 core
out vec4 color;

in vec3 FragPos;  // pos of fragement
in vec3 Normal;  // surface normal
  
uniform vec3 lightPos;  // pos of light source
uniform vec3 viewPos;  // pos of camera
uniform vec3 lightColor;  // color of light source
uniform vec3 objectColor;  // color of object

// TODO: Replace with your code...

vec3 calculateAmbient(vec3 lightColor, vec3 objectColor) {
    float ambientStrength = 0.13;
    return ambientStrength * lightColor * objectColor;
}

vec3 calculateDiffuse(vec3 lightColor, vec3 objectColor, vec3 FragPos, vec3 Normal, vec3 lightPos) {
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseStrength = max(dot(Normal, lightDir), 0.1);
    return diffuseStrength * lightColor * objectColor;
}

vec3 calculateSpecular(vec3 lightColor, vec3 viewPos, vec3 FragPos, vec3 Normal, vec3 lightPos) {
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), 41);
    return specularStrength * 0.61 * lightColor;
}

void main()
{   
    // Ambient section (base level of lighting that is present everywhere regardless of the position of the light source)
    vec3 ambient = calculateAmbient(lightColor, objectColor);

    // Diffuse section (light that is scattered equally in all directions from a surface that is not perfectly smooth)
    vec3 diffuse = calculateDiffuse(lightColor, objectColor, FragPos, Normal, lightPos);

    // Specular section (the bright spot of light that appears on shiny surfaces when illuminated)
    vec3 specular = calculateSpecular(lightColor, viewPos, FragPos, Normal, lightPos);

    // Final product
    vec3 finalColor = ambient + diffuse + specular;
    color = vec4(finalColor, 1.0);
} 