#include "Scene.h"
#include "Utilities/MatrixHandler.h"
Scene::Scene() {
	currentCam = nullptr;
}
void Scene::Draw(GLfloat timeDelta) {
	for (Object* element : objects) {
		element->draw();
		MatrixHandler::rotate(element->getMatRef(), 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));

	}
}
Camera* Scene::getCurrentCam() {
	return this->currentCam;
}
void Scene::AddCamera(Camera* cam, GLboolean setCurrent) {
	cameras.push_back(cam);
	if (setCurrent)
		currentCam = cam;
}
void Scene::AddObject(Object* obj) {
	objects.push_back(obj);
}