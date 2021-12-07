#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "Shaders/ShaderProg.h"
#include "Model.h"
#include "Utilities/MatrixHandler.h"
#include "Utilities/IDrawable.h"
class Object : public IDrawable
{
protected:
	ShaderProg* shaderProgram; 
	glm::mat4 transMat;
	Model* model;
	GLint idModelTransform;
	GLfloat rotationAngle;
	glm::vec3 rotationAxis;
	glm::vec4 color;
	GLint objID;
public:
	Object();
	Object(Model* model, ShaderProg* shaderProgram, GLint objID = 0);
	virtual void draw() override;
	ShaderProg* getShader();
	glm::mat4* getMatRef();
	void setRotation(GLfloat rotationAngle, glm::vec3 rotationAxis);
	void setColor(glm::vec4 color);
	void setColor(glm::vec3 color);
	GLint getObjID();
};

