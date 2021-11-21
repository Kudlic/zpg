#pragma once
#include "Object.h"
#include "Camera.h"
#include "Skybox.h"
#include <vector>
#include "DirectionalLight.h"
#include "PointLight.h"
#include<glm/gtc/type_ptr.hpp>

class Scene
{
private:
	std::vector <Object*> objects;
	std::vector <Camera*> cameras;
	std::vector <PointLight> pointLights;
	glm::vec3 lightPos;
	DirectionalLight dirLight;
	Camera* currentCam;
	Skybox* skybox;
public:
	glm::vec4 background;
	GLint sceneSeq;
	Scene(GLint sceneSeq);
	void draw(GLfloat timeDelta);
	Camera* getCurrentCam();
	void addCamera(Camera* cam, GLboolean setCurrent = true);
	void addLight(PointLight);
	void addObject(Object* obj);
	void setLightPos(glm::vec3 lightPos);
	void setDirLight(DirectionalLight dirLight);
	void setSkybox(Skybox* skybox);
};

