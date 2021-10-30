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
#include "../Utilities/IObserver.h"
#include <glm/gtc/type_ptr.hpp>
#include "ShaderLoader.h"



class ShaderProg : public IObserver 
{
private:
	GLuint shaderProgram;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	glm::vec3 cameraPos;
public:
	ShaderProg(GLuint shaderProgram);
	ShaderProg(const char* vertex_shader, const char* fragment_shader);
	void useShader();
	GLuint getShaderProgram();
	virtual void update(glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 camPos) override;
};