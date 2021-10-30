#include "ShaderProg.h"

ShaderProg::ShaderProg(GLuint shaderProgID) {
	this->shaderProgram = shaderProgID;
}
ShaderProg::ShaderProg(const char* vertex_shader, const char* fragment_shader) {
	ShaderLoader sl = ShaderLoader(vertex_shader, fragment_shader, &this->shaderProgram);
}

void ShaderProg::useShader() {
	glUseProgram(shaderProgram);

	GLint idViewMat = glGetUniformLocation(shaderProgram, "viewMatrix");
	GLint idProjMat = glGetUniformLocation(shaderProgram, "projectionMatrix");
	GLint idCamPos = glGetUniformLocation(shaderProgram, "cameraPos");


	glUniformMatrix4fv(idViewMat, 1, GL_FALSE, &viewMat[0][0]);
	glUniformMatrix4fv(idProjMat, 1, GL_FALSE, &projMat[0][0]);
	glUniform3fv(idCamPos, 1, glm::value_ptr(this->cameraPos));

}

GLuint ShaderProg::getShaderProgram() {
	return shaderProgram;
}

void ShaderProg::update(glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 camPos) {
	this->viewMat = viewMat;
	this->projMat = projMat;
	this->cameraPos = camPos;

}
GLint ShaderProg::getUniformLocation(const char* uniName) {
	return glGetUniformLocation(shaderProgram, uniName);
}



