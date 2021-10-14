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

class ShaderProg {
private:
	GLuint shaderProgram;
public:
	ShaderProg(const char* vertex_shader, const char* fragment_shader);
	void useShader();
	GLuint getShaderProgram();
	
};