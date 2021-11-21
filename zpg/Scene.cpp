#include "Scene.h"
#include "Utilities/MatrixHandler.h"

Scene::Scene(GLint sceneSeq) {
	skybox = nullptr;
	currentCam = nullptr;
	lightPos = glm::vec3(0.0f, 0.0f, 5.0f);
	dirLight = DirectionalLight();
	this->sceneSeq = sceneSeq;
	this->background = glm::vec4(0.2f, 0.2f, 0.2f, 1.f);
}
void Scene::draw(GLfloat timeDelta) {
	if(skybox != nullptr)
		skybox->draw();
	for (Object* element : objects) {
		element->getShader()->useShader();
		dirLight.setAmbientUni(element->getShader()->getUniformLocation("dirLight.ambient"));
		dirLight.setDiffuseUni(element->getShader()->getUniformLocation("dirLight.diffuse"));
		dirLight.setSpecularUni(element->getShader()->getUniformLocation("dirLight.specular"));
		dirLight.setDirectionUni(element->getShader()->getUniformLocation("dirLight.direction"));
		for (int i = 0; i < pointLights.size(); i++) {
			std::string is = std::to_string(i);
			pointLights.at(i).setAmbientUni(element->getShader()->getUniformLocation(((std::string("pointLights[")+ is +std::string("].ambient")).c_str())));
			pointLights.at(i).setDiffuseUni(element->getShader()->getUniformLocation(((std::string("pointLights[") + is + std::string("].diffuse")).c_str())));
			pointLights.at(i).setSpecularUni(element->getShader()->getUniformLocation(((std::string("pointLights[") + is + std::string("].specular")).c_str())));
			pointLights.at(i).setPositionUni(element->getShader()->getUniformLocation(((std::string("pointLights[") + is + std::string("].position")).c_str())));
			pointLights.at(i).setConstantUni(element->getShader()->getUniformLocation(((std::string("pointLights[") + is + std::string("].constant")).c_str())));
			pointLights.at(i).setLinearUni(element->getShader()->getUniformLocation(((std::string("pointLights[") + is + std::string("].linear")).c_str())));
			pointLights.at(i).setQuadraticUni(element->getShader()->getUniformLocation(((std::string("pointLights[") + is + std::string("].quadratic")).c_str())));
		}
		glUniform1i(element->getShader()->getUniformLocation("pointLightsCount"), pointLights.size());
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
void Scene::addLight(PointLight light) {
	pointLights.push_back(light);
}
void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}
void Scene::setLightPos(glm::vec3 lightPos) {
	this->lightPos = lightPos;
}
void Scene::setDirLight(DirectionalLight dirLight) {
	this->dirLight = dirLight;
}
void Scene::setSkybox(Skybox* skybox) {
	this->skybox = skybox;
	this->currentCam->attach(this->skybox);
}
