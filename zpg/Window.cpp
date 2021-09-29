#include <stdexcept>
#include "Window.h"
#include "Engine.h"

Window::Window(int width1, int height1, const char* title){
	width = width1;
	height = height1;
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window, this);
	/*
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->getEngine()->onKey(key, scancode, action, mods);
		});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->getEngine()->onMove(x, y);
		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->getEngine()->onClick(button, action, xpos, ypos);
		});
	*/
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) -> void {
		glViewport(0, 0, w, h);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->width = w;
		win->height = h;
		});
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);  */

	glewExperimental = GL_TRUE;
	glewInit();

	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	//glClearColor(255, 255, 255, 255);
}


bool Window::shouldClose() const {
	return (bool)glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() {
	return window;
}


int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}


Window::~Window() {
	glfwDestroyWindow(window);
}
