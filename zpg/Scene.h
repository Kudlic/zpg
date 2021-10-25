#pragma once
#include "Object.h"
#include "Camera.h"
#include <vector>
class Scene
{
private:
	std::vector <Object*> objects;
	std::vector <Camera*> cameras;
	glm::vec3 lightPos;
	Camera* currentCam;
public:
	Scene();
	void Draw(GLfloat timeDelta);
	Camera* getCurrentCam();
	void AddCamera(Camera* cam, GLboolean setCurrent = true);
	void AddObject(Object* obj);
	void SetLightPos(glm::vec3 lightPos);
};

