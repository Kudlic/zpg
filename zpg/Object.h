#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "Shaders/ShaderProg.h"
#include "Model.h"
#include "Utilities/MatrixHandler.h"
class Object
{
private:
	ShaderProg* shaderProgram;
	glm::mat4 transMat;
	Model* model;
	GLint idModelTransform;
	GLfloat rotationAngle;
	glm::vec3 rotationAxis;
	glm::vec4 color;
public:
	Object(Model* model, ShaderProg* shaderProgram);
	void draw();
	ShaderProg* getShader();
	glm::mat4* getMatRef();
	void setRotation(GLfloat rotationAngle, glm::vec3 rotationAxis);
	void setColor(glm::vec4 color);
	void setColor(glm::vec3 color);
};

