#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//class Engine;

class Window {
public:
	Window(/*Engine* engine,*/ int width, int height, const char* title);
	~Window(); 
	bool shouldClose() const;
	//void swapBuffers() const;
	//void clear() const;

	int getWidth();
	int getHeight();

	//void setViewport();
	//Engine* getEngine();
	GLFWwindow* getWindow();

private:
	//Engine* engine;
	GLFWwindow* window;
	int width, height;
};

