#include "Engine.h"
#include "Fragment_shader.h"
#include "Vertex_shader.h"
#include "Shape.h"

Engine* Engine::instance = 0;

void Engine::init() {

	glfwSetErrorCallback([](int err, const char* description) -> void {
		throw std::runtime_error(description);
		});

	if (!glfwInit()) {
		throw std::runtime_error("failed to init glfw");
		exit(EXIT_FAILURE);
	}

	window = new Window(800, 600, "EngineInitiatedWindow");

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Engine::startRendering() {

	float points1[] = {
   -.5f, -.5f, .5f, 1, 0, 1, 0, 1,
   -.5f, .5f, .5f, 1, 0, 1, 0, 1,
   .5f, -.5f, .5f, 1 , 0, 1, 0, 1,
   .5f, .5f, .5f, 1 , 0, 1, 0, 1
	};
	float points2[] = {
   -.2f, -.8f, .5f, 1, 1, 1, 0, 1,
   -.2f, .8f, .5f, 1, 0, 1, 1, 1,
   .2f, -.8f, .5f, 1 , 1, 0, 1, 1,
   .2f, .8f, .5f, 1 , 0, 1, 0, 1
	};

	Shape *shape1 = new Shape(points1, 4, 4, 4);
	Shape* shape2 = new Shape(points2, 4, 4, 4);

	while (!glfwWindowShouldClose(this->window->getGLFWWindow())) {
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shape1->draw();
	shape2->draw();
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(this->window->getGLFWWindow());
	}

glfwDestroyWindow(this->window->getGLFWWindow());
glfwTerminate();
exit(EXIT_SUCCESS);
}

Window* Engine::getWindow() {
	return this->window;
}

void Engine::onClick(int button, int action, double x, double y) {
	if (action != GLFW_PRESS) {
		return;
	}
}

Engine::Engine() {
	init();
}

Engine* Engine::getInstance()
{
	if (instance == 0)
	{
		instance = new Engine();
	}

	return instance;
}
