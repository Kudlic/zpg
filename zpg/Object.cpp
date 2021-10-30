#include "Object.h"

Object::Object(Model* model, ShaderProg* shaderProgram) {
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->rotationAngle = 0.0f;
	this->rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	this->transMat = glm::mat4(1.0f);
	this->idModelTransform = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "modelMatrix");
}
void Object::draw() {
	shaderProgram->useShader();
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transMat[0][0]);

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