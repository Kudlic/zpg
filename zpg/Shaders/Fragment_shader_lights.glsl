#version 330

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec4 ex_colour;
in vec2 ex_uv;
uniform vec3 lightPos;

uniform vec3 cameraPos;
uniform sampler2D textureUnitID;

uniform DirLight dirLight;
uniform SpotLight flashlight;

#define MAX_POINT_LIGHTS 10  
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightsCount;

out vec4 out_Color;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 toLightVector = normalize(-light.direction);
    // diffuse shading
    float dot_product = max(dot(toLightVector, normalize(normal)), 0.0);
    // specular shading
    vec3 reflectDir = normalize(reflect(-toLightVector, normalize(normal)));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 30);
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * dot_product;
    vec3 specular = light.specular * spec;
    return (vec3(texture(textureUnitID, ex_uv)) * ((ambient) + (diffuse)) + (specular));
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 toLightVector = normalize(light.position - fragPos);
    // diffuse shading
    float dot_product = max(dot(toLightVector, normalize(normal)), 0.0);
    // specular shading
    vec3 reflectDir =  normalize(reflect(-toLightVector,  normalize(normal)));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 30);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * dot_product;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular) * attenuation;
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 toLightVector = normalize(light.position - fragPos);
    // diffuse shading
    float dot_product = max(dot(toLightVector, normalize(normal)), 0.0);
    // specular shading
    vec3 reflectDir =  normalize(reflect(-toLightVector,  normalize(normal)));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 30);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));        
    // spotlight intensity
    float theta = dot(toLightVector, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * dot_product;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular) * attenuation * intensity;
}

void main()
{
  // define an output color value
  vec3 base = vec3(0.0);
  vec3 viewDirection = normalize(cameraPos - ex_worldPosition.xyz);

   // add the directional light's contribution to the base
  base += CalcDirLight(dirLight, ex_worldNormal, viewDirection);
  
  // do the same for all point lights
  for(int i = 0; i < pointLightsCount; i++)
  	base += CalcPointLight(pointLights[i], ex_worldNormal, ex_worldPosition.xyz, viewDirection);
 
  // and add others lights as well (like spotlights)
  base += CalcSpotLight(flashlight, ex_worldNormal, ex_worldPosition.xyz, viewDirection);
  
  out_Color = vec4(base, 1.0);
} 