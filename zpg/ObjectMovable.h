#pragma once
#include "Object.h"
#include "Path.h"
class ObjectMovable :
    public Object
{
private:
public:
    Path path;
    ObjectMovable();
    ObjectMovable(Model* model, ShaderProg* shaderProgram, GLint objID = 0);
    virtual void draw() override;
};

