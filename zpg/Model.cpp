#include "Model.h"

Model::Model(GLboolean bit, const GLfloat* points, int size, int lineLen, int vecLen, int uniformCount, GLenum mode) {

	this->tex = nullptr;
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
Model::Model(const GLfloat* points, GLint pointNo, GLint lineLen) {
	this->tex = nullptr;
	this->pointNo = pointNo;
	this->lineLen = lineLen;
	this->mode = GL_TRIANGLES;
	vbo = new VBO(points, pointNo * lineLen);
	vao = new VAO();
	vao->bind();
}
ModelBuilder Model::create(const GLfloat* points, GLint pointNo, GLint lineLen) {
	return ModelBuilder(points, pointNo, lineLen);
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
void Model::bindTexture(Texture* tex) {
	this->tex = tex;
}
