#include "PointLight.h"
PointLight::PointLight() : Light() {
	this->position = glm::vec3(.0f, 5.f, .0f);
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}
PointLight::PointLight(glm::vec3 position) : position(position), Light() {
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}
PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position): position(position), Light(ambient, diffuse, specular) {
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}
void PointLight::setPositionUni(GLint location) {
	glUniform3fv(location, 1, glm::value_ptr(this->position));
}
void PointLight::setConstantUni(GLint location) {
	glUniform1f(location, this->constant);
}
void PointLight::setLinearUni(GLint location) {
	glUniform1f(location, this->linear);
}
void PointLight::setQuadraticUni(GLint location) {
	glUniform1f(location, this->quadratic);
}
void PointLight::setPosition(glm::vec3 position) {
	this->position = position;
}