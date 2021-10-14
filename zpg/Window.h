#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, const char* title);
	~Window(); 
	bool shouldClose() const;
	//void swapBuffers() const;
	//void clear() const;

	int getWidth();
	int getHeight();

	//void setViewport();
	GLFWwindow* getGLFWWindow();

private:
	GLFWwindow* window;
	int width, height;
};

