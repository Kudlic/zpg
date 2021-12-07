#include "ObjectMovable.h"

ObjectMovable::ObjectMovable(Model* model, ShaderProg* shaderProgram, GLint objID) : Object(model, shaderProgram, objID) {
	this->path = Path();
}
void ObjectMovable::draw() {

	MatrixHandler::reset(this->getMatRef());
	MatrixHandler::translate(this->getMatRef(), this->path.getNextPoint(0.0015f));

	shaderProgram->useShader();
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transMat[0][0]);
	glUniform4fv(shaderProgram->getUniformLocation("in_colour"), 1, glm::value_ptr(this->color));

	if (this->model->tex != nullptr) {
		this->model->tex->useTexture(shaderProgram);
	}
	this->model->getVAO()->bind();
	glDrawArrays(model->getMode(), 0, model->getPointNo());

}