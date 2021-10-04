#pragma once

#include <stdexcept>
#include <glm/vec4.hpp>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape {
private:
public:
	GLuint VBO;
	GLuint VAO;
	GLuint shaderProgram;

	float *points_colors;
	int pointCount;
	int pointLen;
	int colorLen;

	void init();
	Shape(float * points_colors, int pointLen, int colorLen, int pointCount);
	void draw();
};