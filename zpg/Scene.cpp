#include "Scene.h"
Scene::Scene() {
	currentCam = nullptr;
}
void Draw(GLfloat timeDelta) {

}
Camera* Scene::gerCurrentCam() {
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