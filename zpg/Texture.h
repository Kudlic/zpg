#pragma once
#include <SOIL.h>
#include <memory>
#include <string>
#include "Shaders/ShaderProg.h"
#include "stb_image.h"


class Texture {
public:
    Texture();
    //Texture(const char* path, int index);
    int getIndex();
    void useTexture(ShaderProg *sp);

protected:
    GLuint textureID;
    int index;
};