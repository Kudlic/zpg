#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VAO.h"
#include "VBO.h"

class Model {
private:
    int pointNo;
    VAO* vao;
    VBO* vbo;
    GLenum mode;
public:
    Model(const GLfloat *points, int size, GLenum mode = GL_TRIANGLES);
    VAO* getVAO();
    VBO* getVBO();
    int getPointNo();
    GLenum getMode();
};
