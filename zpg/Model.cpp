#include "Model.h"

Model::Model(const GLfloat* points, int size, GLenum mode) {

	pointNo = size / 6;
	this->mode = mode;
	vbo = new VBO(points, size);

	vao = new VAO();
	vao->Bind();
	vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	vao->Unbind();
	vbo->Unbind();
}

VAO* Model::getVAO() {
	return vao;
}

VBO* Model::getVBO() {
	return vbo;
}
int Model::getPointNo() {
	return pointNo;
}
GLenum Model::getMode() {
	return mode;
}
