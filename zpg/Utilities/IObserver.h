#pragma once
#include <iostream>
#include <list>
#include <string>
#include <glm/mat4x4.hpp>


class IObserver {
public:
	virtual ~IObserver() {};
	virtual void Update(glm::mat4 viewMat, glm::mat4 projMat) = 0;
};