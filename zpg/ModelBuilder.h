#pragma once
#include "Model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Model;
class ModelBuilder
{
private:
	Model* model;
public:
	ModelBuilder(const GLfloat* points, GLint pointNo, GLint lineLen);
	ModelBuilder(const char* data);
	ModelBuilder mode(GLenum mode);
	ModelBuilder positionAttrib(GLint at);
	ModelBuilder normalAttrib(GLint at);
	ModelBuilder texAttrib(GLint at);
	ModelBuilder colorAttrib(GLint at, GLboolean alpha = 0);
	Model* build();
};

