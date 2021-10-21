#include "Object.h"

Object::Object(Model* model, ShaderProg* shaderProgram) {
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transMat = glm::mat4(1.0f);
	this->idModelTransform = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "modelMatrix");
}
void Object::draw() {
	shaderProgram->useShader();
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transMat[0][0]);

	this->model->getVAO()->Bind();
	glDrawArrays(model->getMode(), 0, model->getPointNo());

}
ShaderProg* Object::getShader() {
	return this->shaderProgram;
}
glm::mat4* Object::getMatRef() {
	return &this->transMat;
}
