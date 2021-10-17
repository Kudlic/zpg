#pragma once

#include <stdexcept>
#include <glm/vec4.hpp>
#include <memory>
#include "Scene.h"
#include "Window.h"

class Engine{
private:
	Window* window;
	static Engine* instance;
	Scene* currentScene;
	Engine();

public:
	void init();

	void startRendering();

	virtual void onKey(int key, int scancode, int action, int mods);
	virtual void onMove(double x, double y);
	virtual void onClick(int button, int action, double x, double y);
	void processHeldKeys();

	Window* getWindow();

	static Engine* getInstance();

	//Scene *getScene();


};


