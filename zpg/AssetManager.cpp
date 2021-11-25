#include "AssetManager.h"
#include "ModelFactory.h"

AssetManager* AssetManager::instance = 0;

AssetManager::AssetManager() {
	init();
}

AssetManager* AssetManager::getInstance()
{
	if (instance == 0)
	{
		instance = new AssetManager();
	}

	return instance;
}
void AssetManager::init() {
	this->saveModelByName(ModelFactory::premade(ModelType::treeO), "texturedTree1");
	this->saveModelByName(ModelFactory::premade(ModelType::houseTextured), "texturedHouse1");
}
ShaderProg* AssetManager::getShaderByName(std::string name) {
	for (KeyPtr element : this->shaders) {
		if (element.key == name) {
			return (ShaderProg*)element.ptr;
		}
	}
}
bool AssetManager::saveShaderByName(ShaderProg* sp, std::string name) {
	for (KeyPtr element : this->shaders) {
		if (element.key == name) {
			return false;
		}
	}
	KeyPtr toPush;
	toPush.key = name;
	toPush.ptr = (void*)sp;
	this->shaders.push_back(toPush);
	return true;
}
Model* AssetManager::getModelByName(std::string name) {
	for (KeyPtr element : this->models) {
		if (element.key == name) {
			return (Model*)element.ptr;
		}
	}
}
bool AssetManager::saveModelByName(Model* m, std::string name) {
	for (KeyPtr element : this->shaders) {
		if (element.key == name) {
			return false;
		}
	}
	KeyPtr toPush;
	toPush.key = name;
	toPush.ptr = (void*)m;
	this->models.push_back(toPush);
	return true;
}