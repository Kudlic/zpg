#pragma once
#include <iostream>

class IDrawable {
public:
	virtual ~IDrawable() {};
	virtual void draw() {};
};