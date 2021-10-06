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
   -.4f, -.7f, .5f, 1,		1, 1, .4f, 1,
   -.4f,  .3f, .5f, 1,		1, 1, .4f, 1,
    .4f, -.7f, .5f, 1 ,		1, 1, .4f, 1,
    .4f,  .3f, .5f, 1 ,		1, 1, .4f, 1,

	.4f, -.7f, -.5f, 1,		0.85f, 0.85f, .3f, 1,
    .4f,  .3f, -.5f, 1,		0.85f, 0.85f, .3f, 1,

	-.4f, -.7f, -.5f, 1,	1, 1, .4f, 1,
	-.4f,  .3f, -.5f, 1,	1, 1, .4f, 1,

	-.4f, -.7f, .5f, 1,		0.85f, 0.85f, .3f, 1,
   -.4f,  .3f, .5f, 1,		0.85f, 0.85f, .3f, 1,
	};
	float points2[] = {
   -.6f,  .3f, .5f, 1,		1, 0, 0, 1,
    .6f,  .3f, .5f, 1,		.7f, 0, 0, 1,
	.0f , .9f, .5f, 1 ,		1, 0, 0, 1,
	.6f,  .3f, -.5f, 1,		1, 0, 0, 1,
	.0f , .9f, -.5f, 1 ,	.7f, 0, 0, 1,
	-.6f,  .3f, -.5f, 1,	1, 0, 0, 1,
	.0f , .9f, .5f, 1 ,		1, 0, 0, 1,
	-.6f,  .3f, .5f, 1,		.7f, 0, 0, 1
	};
	float points3[] = {
    .1f, -.7f, -.51f, 1,	.4f, .2f, .0f, 1,
    .1f, -.2f, -.51f, 1,	.4f, .2f, .0f, 1,
	.3f, -.7f, -.51f, 1 ,	.4f, .2f, .0f, 1,
	.3f, -.2f, -.51f, 1 ,	.4f, .2f, .0f, 1
	};

	Shape *walls = new Shape(points1, 4, 4, 10);
	Shape *roof = new Shape(points2, 4, 4, 8);
	Shape* door = new Shape(points3, 4, 4, 4);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	while (!glfwWindowShouldClose(this->window->getGLFWWindow())) {
	// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		walls->draw();
		walls->rotate(0.02f, yAxis);
		roof->draw();
		roof->rotate(0.02f, yAxis);
		//roof->scale(glm::vec3(1.01f, 1.01f, 1.0f));
		door->draw();
		door->rotate(0.02f, yAxis);
		//door->translate(glm::vec3(0.01f, 0.0f, 0.0f));

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
