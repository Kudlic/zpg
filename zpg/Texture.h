#pragma once
#include <SOIL.h>
#include <memory>
#include <string>
#include "Shaders/ShaderProg.h"

class Texture {
public:
    Texture();
    Texture(const char* path, int index);
    int getIndex();
    void useTexture(ShaderProg *sp);

private:
    GLuint textureID;
    int index;
};