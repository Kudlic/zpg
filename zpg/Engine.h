#pragma once

#include <stdexcept>
#include <glm/vec4.hpp>
#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags#include <memory>
#include "Scene.h"
#include "Window.h"

class Engine{
private:
	Window* window;
	static Engine* instance;
	std::vector <Scene*> scenes;
	Engine();

public:
	std::vector <ShaderProg*> shaders;
	Scene* currentScene;
	
	void init();

	void startRendering();
	void initScenes();

	virtual void onKey(int key, int scancode, int action, int mods);
	virtual void onMove(double x, double y);
	virtual void onClick(int button, int action, double x, double y);
	void processHeldKeys();
	void nextScene();
	GLint genIndex();

	Window* getWindow();

	static Engine* getInstance();

	//Scene *getScene();


};


