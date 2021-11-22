#include "ReflectorLight.h"
ReflectorLight::ReflectorLight(): PointLight() {
	this->direction = (glm::vec3(0.f, 0.f, 1.f));
	this->cutOff = glm::cos(glm::radians(12.5f));
	this->outerCutOff = glm::cos(glm::radians(15.f));
}
ReflectorLight::ReflectorLight(glm::vec3 direction, glm::vec3 position) : PointLight(position){
	this->direction = direction;
	this->cutOff = glm::cos(glm::radians(12.5f));
	this->outerCutOff = glm::cos(glm::radians(15.f));
}
ReflectorLight::ReflectorLight(glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 position) : PointLight(position) {
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}
ReflectorLight::ReflectorLight(glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position) 
	: PointLight( ambient, diffuse, specular, direction)
{
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}
void ReflectorLight::setCutOffUni(GLint location) {
	glUniform1f(location, this->cutOff);
}
void ReflectorLight::setOuterCutOffUni(GLint location) {
	glUniform1f(location, this->outerCutOff);
}
void ReflectorLight::setDirectionUni(GLint location) {
	glUniform3fv(location, 1, glm::value_ptr(this->direction));
}
void ReflectorLight::setDirection(glm::vec3 direction) {
	this->direction = direction;
}