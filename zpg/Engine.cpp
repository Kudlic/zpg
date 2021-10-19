#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Object.h"
#include "Shaders/ShaderProg.h"
#include "Utilities/MatrixHandler.h"
#include "Camera.h"
#include "Scene.h"
#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"




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

	const float points1[] = {
   -.4f, -.7f, .5f, 		1, 1, .4f, 
   -.4f,  .3f, .5f, 		1, 1, .4f, 
	.4f, -.7f, .5f, 		1, 1, .4f, 
	.4f,  .3f, .5f, 		1, 1, .4f, 

	.4f, -.7f, -.5f, 		0.85f, 0.85f, .3f, 
	.4f,  .3f, -.5f, 		0.85f, 0.85f, .3f, 

	-.4f, -.7f, -.5f, 		1, 1, .4f, 
	-.4f,  .3f, -.5f, 		1, 1, .4f, 

	-.4f, -.7f, .5f, 		0.85f, 0.85f, .3f, 
   -.4f,  .3f, .5f, 		0.85f, 0.85f, .3f, 
	};
	const float points2[] = {
   -.6f,  .3f, .75f, 		1, 0, 0, 
	.6f,  .3f, .75f, 		.7f, 0, 0,
	.0f , .9f, .45f, 	1, 0, 0, 
	.6f,  .3f, -.75f, 	1, 0, 0, 
	.0f , .9f, -.45f, 	.7f, 0, 0,
	-.6f,  .3f, -.75f, 	1, 0, 0, 
	.0f , .9f, .45f, 	1, 0, 0, 
	-.6f,  .3f, .75f, 	.7f, 0, 0
	};
	const float points3[] = {
	.1f, -.7f, -.51f,	.4f, .2f, .0f, 
	.1f, -.2f, -.51f,	.4f, .2f, .0f, 
	.3f, -.7f, -.51f, 	.4f, .2f, .0f, 
	.3f, -.2f, -.51f, 	.4f, .2f, .0f, 
	};

	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	glfwSetCursorPos(window->getGLFWWindow(), (window->getWidth() / 2), (window->getHeight() / 2));

	ShaderProg* sp = new ShaderProg(vertex_shader, fragment_shader);
	Object* cube = new Object(new Model(points1, 10 * (3 + 3), GL_TRIANGLE_STRIP), sp);
	Object* roof = new Object(new Model(points2, 8 * (3 + 3), GL_TRIANGLE_STRIP), sp);
	Object* sphereO = new Object(new Model(sphere, 2880 * (3 + 3), GL_TRIANGLES), sp);
	MatrixHandler::translate(sphereO->getMatRef(), glm::vec3(0.0f, 0.0f, 10.0f));

	Object* plainO = new Object(new Model(plain, 6 * (3 + 3), GL_TRIANGLES), sp);
	MatrixHandler::translate(plainO->getMatRef(), glm::vec3(-5.0f, 0.0f, 5.0f));
	MatrixHandler::rotate(plainO->getMatRef(), 45 , zAxis);


	Object* suziFlatO = new Object(new Model(suziFlat, 2904 * (3 + 3), GL_TRIANGLES), sp);
	MatrixHandler::translate(suziFlatO->getMatRef(), glm::vec3(5.0f, 0.0f, 2.0f));

	Object* suziSmoothO = new Object(new Model(suziSmooth, 2904 * (3 + 3), GL_TRIANGLES), sp);
	MatrixHandler::translate(suziSmoothO->getMatRef(), glm::vec3(5.0f, 0.0f, 8.0f));


	Camera* camera = new Camera(window->getWidth(), window->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f));

	this->currentScene = new Scene();
	currentScene->AddCamera(camera);
	currentScene->AddObject(cube);
	currentScene->AddObject(roof);
	currentScene->AddObject(sphereO);
	currentScene->AddObject(plainO);
	currentScene->AddObject(suziFlatO);
	currentScene->AddObject(suziSmoothO);

	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(this->window->getGLFWWindow())) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currentScene->getCurrentCam()->UpdateShader(sp->getShaderProgram());
		currentScene->Draw(deltaTime);
		processHeldKeys();

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
	printf("move %f %f \n", x, y);
	double xmove, ymove;
	xmove = x - (window->getWidth() / 2);
	ymove = y - (window->getHeight() / 2);

	glfwSetCursorPos(window->getGLFWWindow(), (window->getWidth() / 2), (window->getHeight() / 2));

	this->currentScene->getCurrentCam()->Rotate(xmove, ymove);

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
void Engine::processHeldKeys() {
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->Move(CAM_FORWARD);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->Move(CAM_LEFT);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->Move(CAM_BACKWARD);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->Move(CAM_RIGHT);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->Move(CAM_UP);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->Move(CAM_DOWN);
	}
}