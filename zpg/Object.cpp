#include "Object.h"

Object::Object(Model* model, ShaderProg* shaderProgram) {
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->rotationAngle = 0.0f;
	this->rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	this->transMat = glm::mat4(1.0f);
	this->idModelTransform = this->shaderProgram->getUniformLocation("modelMatrix");
	this->color = glm::vec4(1.0f, 0.7f, 0.05f, 1.f);
}
void Object::draw() {
	shaderProgram->useShader();
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transMat[0][0]);
	glUniform4fv(shaderProgram->getUniformLocation("in_colour"), 1, glm::value_ptr(this->color));

	this->model->getVAO()->bind();
	glDrawArrays(model->getMode(), 0, model->getPointNo());
	MatrixHandler::rotate(this->getMatRef(), this->rotationAngle, this->rotationAxis);

}
ShaderProg* Object::getShader() {
	return this->shaderProgram;
}
glm::mat4* Object::getMatRef() {
	return &this->transMat;
}
void Object::setRotation(GLfloat rotationAngle, glm::vec3 rotationAxis) {
	this->rotationAxis = rotationAxis;
	this->rotationAngle = rotationAngle;
}
void Object::setColor(glm::vec4 color) {
	this->color = color;
}
void Object::setColor(glm::vec3 color) {
	this->color = glm::vec4(color, 1);
}