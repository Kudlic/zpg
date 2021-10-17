#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "Shaders/ShaderProg.h"
#include "Model.h"
class Object
{
private:
	ShaderProg* shaderProgram;
	glm::mat4 transMat;
	Model* model;
	GLint idModelTransform;
public:
	Object(Model* model, ShaderProg* shaderProgram);
	void draw();
	ShaderProg* getShader();
	glm::mat4* getMatRef();
};

