#pragma once
#include <stdexcept>
#include <glm/vec4.hpp>
#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags#include <memory>
#include <vector>
#include "Shaders/ShaderProg.h"
#include "Model.h"
#include <string>

struct KeyPtr{
	string key;
	void* ptr;
};

class AssetManager
{
private:
	static AssetManager* instance;
	std::vector <KeyPtr> shaders;
	std::vector <KeyPtr> models;
	AssetManager();
public:
	void init();
	static AssetManager* getInstance();
	ShaderProg* getShaderByName(std::string name);
	bool saveShaderByName(ShaderProg* sp, std::string name);
	Model* getModelByName(std::string name);
	bool saveModelByName(Model* m, std::string name);
};


