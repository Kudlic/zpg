#pragma once
#include "Utilities/IDrawable.h"
#include "Object.h"
#include "Shaders/ShaderProg.h"
#include "Utilities/IPositionObserver.h"
#include <glm/glm.hpp>

class Skybox : public IDrawable, public IPositionObserver
{
private:
	Object sides[6];
	glm::vec3 position;
public:
	Skybox(ShaderProg* sp);
	virtual void draw() override;
	virtual void update(glm::vec3 position) override;
};

