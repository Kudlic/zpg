#pragma once

#include <stdexcept>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape {
private:
	GLuint VBO;
	GLuint VAO;
	GLuint shaderProgram;
	GLint idModelTransform;
	glm::mat4 transMat;

	float *points_colors;
	int pointCount;
	int pointLen;
	int colorLen;

	void init();
public:
	Shape(float * points_colors, int pointLen, int colorLen, int pointCount);
	void draw();
	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 transVec);
	void scale(glm::vec3 scaleVec);
};