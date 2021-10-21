#include "Scene.h"
#include "Utilities/MatrixHandler.h"
Scene::Scene() {
	currentCam = nullptr;
	lightPos = glm::vec3(0.0f, 0.0f, 5.0f);
}
void Scene::Draw(GLfloat timeDelta) {
	for (Object* element : objects) {
		glUniform3fv(glGetUniformLocation(element->getShader()->getShaderProgram(), "lightPos"), 1, glm::value_ptr(this->lightPos));

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