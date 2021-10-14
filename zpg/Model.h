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
public:
    Model(GLfloat *points, int size);
    VAO* getVAO();
    VBO* getVBO();
    int getPointNo();

};
