#include "DirectionalLight.h"
DirectionalLight::DirectionalLight():Light() {
	this->direction = glm::vec3(.0f, -1.f, .0f);
}
DirectionalLight::DirectionalLight(glm::vec3 direction) : direction(direction) {

}
DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) 
	: direction(direction), Light(ambient, diffuse, specular){
}
void DirectionalLight::setDirectionUni(GLint location) {
	glUniform3fv(location, 1, glm::value_ptr(this->direction));
}
