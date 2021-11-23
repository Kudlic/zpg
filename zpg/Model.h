#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VAO.h"
#include "VBO.h"
#include "ModelBuilder.h"
#include "Texture.h"
#include "TextureRGB.h"
#include "TextureRGBA.h"
#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags#include <memory>

class ModelBuilder;

class Model {
private:
    GLint pointNo;
    GLint lineLen;
    VAO* vao;
    VBO* vbo;
    GLenum mode;

public:
    friend class ModelBuilder;
    Texture* tex;
    Model(GLboolean bit, const GLfloat *points, int size, int lineLen, int vecLen = 3, int uniformCount = 0, GLenum mode = GL_TRIANGLES);
    Model(const GLfloat* points, GLint pointNo, GLint lineLen);
    Model(const char* modelData);
    static ModelBuilder create(const GLfloat* points, GLint pointNo, GLint lineLen);
    static ModelBuilder create(const char* modelData);
    VAO* getVAO();
    VBO* getVBO();
    int getPointNo();
    GLenum getMode();
    void bindTexture(Texture* tex);
};
