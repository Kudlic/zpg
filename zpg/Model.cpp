#include "Model.h"

Model::Model(GLfloat* points, int size) {

	pointNo = size / 8;
	vbo = new VBO(points, sizeof(points)*size);

	vao = new VAO();
	vao->Bind();
	vao->LinkAttrib(*vbo, 0, 4, GL_FLOAT, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	vao->LinkAttrib(*vbo, 1, 4, GL_FLOAT, 8 * sizeof(GL_FLOAT), (GLvoid*)(4 * sizeof(GL_FLOAT)));
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