#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec4 ex_colour;

uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec4 out_Color;
void main(void)
{
//vec3 lightPosition= vec3(10.0,10.0,10.0); //správně upravit
//Ambient light
vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);
vec3 baseColor = vec3(1.0f, 0.7f, 0.05f);
//Diffusion
vec3 toLightVector = normalize(lightPos - ex_worldPosition.xyz);
float dot_product = max(dot(toLightVector, normalize(ex_worldNormal)), 0.0);
vec3 diffuse = dot_product * vec3( 1.0f, 1.0f, 1.0f);
//Specular
vec3 fromLightVector = normalize(ex_worldPosition.xyz - lightPos);
vec3 reflectFromLightVector = normalize(reflect(fromLightVector, normalize(ex_worldNormal)));
vec3 toCamVector = normalize(cameraPos - ex_worldPosition.xyz);
float specularConstant = pow(max(dot(toCamVector, reflectFromLightVector),0), 30);
vec3 specular = vec3(1.f, 1.f, 1.f) * specularConstant;
//Output
out_Color = ex_colour * (vec4(ambientLight, 1.f)
        +   vec4(diffuse, 1.f) + vec4(specular, 1.f)); 
}
