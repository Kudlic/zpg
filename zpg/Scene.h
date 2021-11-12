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
	glm::vec4 background;
	GLint sceneSeq;
	Scene(GLint sceneSeq);
	void draw(GLfloat timeDelta);
	Camera* getCurrentCam();
	void addCamera(Camera* cam, GLboolean setCurrent = true);
	void addObject(Object* obj);
	void setLightPos(glm::vec3 lightPos);
};

