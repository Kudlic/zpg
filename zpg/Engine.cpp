#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Object.h"
#include "Shaders/ShaderProg.h"
#include "Utilities/MatrixHandler.h"
#include "Camera.h"


Engine* Engine::instance = 0;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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
   -.6f,  .3f, .75f, 1,		1, 0, 0, 1,
	.6f,  .3f, .75f, 1,		.7f, 0, 0, 1,
	.0f , .9f, .45f, 1 ,	1, 0, 0, 1,
	.6f,  .3f, -.75f, 1,	1, 0, 0, 1,
	.0f , .9f, -.45f, 1 ,	.7f, 0, 0, 1,
	-.6f,  .3f, -.75f, 1,	1, 0, 0, 1,
	.0f , .9f, .45f, 1 ,	1, 0, 0, 1,
	-.6f,  .3f, .75f, 1,	.7f, 0, 0, 1
	};
	float points3[] = {
	.1f, -.7f, -.51f, 1,	.4f, .2f, .0f, 1,
	.1f, -.2f, -.51f, 1,	.4f, .2f, .0f, 1,
	.3f, -.7f, -.51f, 1 ,	.4f, .2f, .0f, 1,
	.3f, -.2f, -.51f, 1 ,	.4f, .2f, .0f, 1
	};

	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	ShaderProg* sp = new ShaderProg(vertex_shader, fragment_shader);
	Object* cube = new Object(new Model(points1,10 * (4 + 4)), sp);
	Object* roof = new Object(new Model(points2, 8 * (4 + 4)), sp);

	Camera* camera = new Camera(window->getWidth(), window->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f));

	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(this->window->getGLFWWindow())) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera->UpdateShader(sp->getShaderProgram());

		cube->draw();
		roof->draw();
		MatrixHandler::rotate(cube->getMatRef(), 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));
		MatrixHandler::rotate(roof->getMatRef(), 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));

		//camera->Move(CAM_LEFT);
		camera->Rotate(1, 0);
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
	if (action == GLFW_PRESS) {
		printf("press %d %d %f %f\n", button, action, x, y);
	}
	if (action == GLFW_RELEASE) {
		printf("release %d %d %f %f\n", button, action, x, y);
	}
	return;
}
void Engine::onKey(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		printf("press %d %d %d %d\n", key, scancode, action, mods);
	}
	if (action == GLFW_RELEASE) {
		printf("release %d %d %d %d\n", key, scancode, action, mods);
	}
	return;
}
void Engine::onMove(double x, double y) {
	
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
