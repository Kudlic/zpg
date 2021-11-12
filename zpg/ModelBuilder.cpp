#include "ModelBuilder.h"
ModelBuilder::ModelBuilder(const GLfloat* points, int pointNo, int lineLen) {
	this->model = new Model(points, pointNo, lineLen);
}
ModelBuilder ModelBuilder::mode(GLenum mode) {
	this->model->mode = mode;
	return *this;
}
ModelBuilder ModelBuilder::positionAttrib(GLint at) {
	this->model->vao->bind();
	this->model->vao->linkAttrib(*this->model->vbo, 0, 3, GL_FLOAT, this->model->lineLen * sizeof(GL_FLOAT), (GLvoid*)(at * sizeof(GL_FLOAT)));
	this->model->vao->unbind();
	return *this;
}
ModelBuilder ModelBuilder::normalAttrib(GLint at) {
	this->model->vao->bind();
	this->model->vao->linkAttrib(*this->model->vbo, 1, 3, GL_FLOAT, this->model->lineLen * sizeof(GL_FLOAT), (GLvoid*)(at * sizeof(GL_FLOAT)));
	this->model->vao->unbind();
	return *this;
}
ModelBuilder ModelBuilder::texAttrib(GLint at) {
	this->model->vao->bind();
	this->model->vao->linkAttrib(*this->model->vbo, 3, 2, GL_FLOAT, this->model->lineLen * sizeof(GL_FLOAT), (GLvoid*)(at * sizeof(GL_FLOAT)));
	this->model->vao->unbind();
	return *this;
}
ModelBuilder ModelBuilder::colorAttrib(GLint at, GLboolean alpha) {
	this->model->vao->bind();
	GLint componentNo;
	if(alpha)
		componentNo = 4;
	else
		componentNo = 3;
	this->model->vao->linkAttrib(*this->model->vbo, 2, componentNo, GL_FLOAT, this->model->lineLen * sizeof(GL_FLOAT), (GLvoid*)(at * sizeof(GL_FLOAT)));
	this->model->vao->unbind();
	return *this;
}
Model* ModelBuilder::build() {
	this->model->vao->unbind();
	this->model->vbo->unbind();
	return this->model;
}