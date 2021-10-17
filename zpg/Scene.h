#pragma once
#include "Object.h"
#include "Camera.h"
#include <vector>
class Scene
{
private:
	std::vector <Object*> objects;
	std::vector <Camera*> cameras;
	Camera* currentCam;
public:
	Scene();
	void Draw(GLfloat timeDelta);
	Camera* gerCurrentCam();
	void AddCamera(Camera* cam, GLboolean setCurrent = true);
	void AddObject(Object* obj);

};

