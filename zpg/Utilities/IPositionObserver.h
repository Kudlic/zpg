#pragma once
#include <iostream>
#include <list>
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class IPositionObserver {
public:
	virtual ~IPositionObserver() {};
	virtual void update(glm::vec3 position) = 0;
};