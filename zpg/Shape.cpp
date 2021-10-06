#include "Shape.h"
#include "Fragment_shader.h"
#include "Vertex_shader.h"
#include "Engine.h"
#include <iostream>


Shape::Shape(float* points_colors, int pointLen, int colorLen, int pointCount) {

	this->pointCount = pointCount;
	this->points_colors = points_colors;
	this->pointLen = pointLen;
	this->colorLen = colorLen;
	this->transMat = glm::mat4(1.0f);

	this->init();
}
void Shape::init() {
	int rowlen = this->pointLen + this->colorLen;
	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->points_colors)*rowlen*this->pointCount, this->points_colors, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, this->pointLen, GL_FLOAT, GL_FALSE, /*(this->colorLen + this->pointLen)*/8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glVertexAttribPointer(1, this->colorLen, GL_FLOAT, GL_FALSE, /*(this->colorLen + this->pointLen) */8 *sizeof(GL_FLOAT), (GLvoid*)(this->pointLen * sizeof(GL_FLOAT)));

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, fragmentShader);
	glAttachShader(this->shaderProgram, vertexShader);
	glLinkProgram(this->shaderProgram);

	this->idModelTransform = glGetUniformLocation(this->shaderProgram, "modelMatrix");

	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

}
void Shape::draw() {
	glUseProgram(this->shaderProgram);
	glUniformMatrix4fv(this->idModelTransform, 1, GL_FALSE, &this->transMat[0][0]);
	glBindVertexArray(this->VAO);
	// draw triangles
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->pointCount);
}
void Shape::rotate(float angle, glm::vec3 axis) {
	this->transMat = glm::rotate(this->transMat, angle, axis);
}
void Shape::translate(glm::vec3 transVec) {
	this->transMat = glm::translate(this->transMat, transVec);
}
void Shape::scale(glm::vec3 scaleVec) {
	this->transMat = glm::scale(this->transMat, scaleVec);
}
