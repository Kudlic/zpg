#include "Light.h"
Light::Light() {
	this->ambient = glm::vec3(.2f, .2f, .2f);
	this->diffuse = glm::vec3(1.f, 1.f, 1.f);
	this->specular = glm::vec3(1.f, 1.f, 1.f);
}
Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :ambient(ambient), diffuse(diffuse), specular(specular){

}
void Light::setAmbientUni(GLint location) {
	glUniform3fv(location, 1, glm::value_ptr(this->ambient));
}
void Light::setDiffuseUni(GLint location) {
	glUniform3fv(location, 1, glm::value_ptr(this->diffuse));
}
void Light::setSpecularUni(GLint location) {
	glUniform3fv(location, 1, glm::value_ptr(this->specular));
}