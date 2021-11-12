#include "Scene.h"
#include "Utilities/MatrixHandler.h"

Scene::Scene(GLint sceneSeq) {
	currentCam = nullptr;
	lightPos = glm::vec3(0.0f, 0.0f, 5.0f);
	this->sceneSeq = sceneSeq;
	this->background = glm::vec4(0.2f, 0.2f, 0.2f, 1.f);
}
void Scene::draw(GLfloat timeDelta) {
	for (Object* element : objects) {
		glUniform3fv(element->getShader()->getUniformLocation("lightPos"), 1, glm::value_ptr(this->lightPos));
		element->draw();
	}
}
Camera* Scene::getCurrentCam() {
	return this->currentCam;
}
void Scene::addCamera(Camera* cam, GLboolean setCurrent) {
	cameras.push_back(cam);
	if (setCurrent)
		currentCam = cam;
}
void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}
void Scene::setLightPos(glm::vec3 lightPos) {
	this->lightPos = lightPos;
}