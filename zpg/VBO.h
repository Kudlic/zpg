#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(const GLfloat* vertices, GLint verticesSize);

	// Binds the VBO
	void bind();
	// Unbinds the VBO
	void unbind();
	// Deletes the VBO
	void del();

};

