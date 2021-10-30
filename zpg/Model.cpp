#include "Model.h"

Model::Model(const GLfloat* points, int size, int lineLen, int vecLen, int uniformCount, GLenum mode) {

	pointNo = size / lineLen;
	this->mode = mode;
	vbo = new VBO(points, size);

	int i_top = 0;

	if (uniformCount == 0)
		i_top = lineLen / vecLen;
	else
		i_top = uniformCount;


	vao = new VAO();
	vao->bind();
	for(int i =0; i < i_top; i++){
		vao->linkAttrib(*vbo, i, vecLen, GL_FLOAT, lineLen * sizeof(GL_FLOAT), (GLvoid*)(i* vecLen * sizeof(GL_FLOAT)));
	}
	vao->unbind();
	vbo->unbind();
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
