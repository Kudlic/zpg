#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Shaders/ShaderProg.h"
#include "Shaders/ShaderLoader.h"
#include "Object.h"
#include "Utilities/MatrixHandler.h"
#include "Camera.h"
#include "Scene.h"
#include "ModelFactory.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Engine* Engine::instance = 0;
GLint sceneSeq = 0;
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

	glfwSetInputMode(window->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window->getGLFWWindow(), (window->getWidth() / 2), (window->getHeight() / 2));
	this->initScenes();
}
void Engine::initScenes() {
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

	ShaderProg* colSp = new ShaderProg("./Shaders/vertex_shader.glsl", "./Shaders/fragment_shader.glsl");
	ShaderProg* constSp = new ShaderProg("./Shaders/vertex_shader_constant.glsl", "./Shaders/fragment_shader_constant.glsl");
	ShaderProg* lambSp = new ShaderProg("./Shaders/vertex_shader_lambert.glsl", "./Shaders/fragment_shader_lambert.glsl");
	ShaderProg* phongSp = new ShaderProg("./Shaders/vertex_shader_phong.glsl", "./Shaders/fragment_shader_phong.glsl");

	Object* cube = new Object(Model::create(points1, 10, 6).positionAttrib(0).mode(GL_TRIANGLE_STRIP).build(), constSp);

	Object* roof = new Object(Model::create(points2, 8, 6).positionAttrib(0).colorAttrib(3).mode(GL_TRIANGLE_STRIP).build(), colSp);

	Object* sphereO = new Object(ModelFactory::premade(ModelType::sphereC), colSp);
	sphereO->setRotation(0.8f, glm::vec3(.0f, .0f, 1.0f));
	MatrixHandler::translate(sphereO->getMatRef(), glm::vec3(0.0f, 0.0f, 10.0f));

	Object* plainO = new Object(ModelFactory::premade(ModelType::plainN), phongSp);
	MatrixHandler::scale(plainO->getMatRef(), glm::vec3(.3f, .3f, .3f));
	MatrixHandler::translate(plainO->getMatRef(), glm::vec3(0.0f, -1.0f, 5.0f));
	
	Object* suziFlatO = new Object(ModelFactory::premade(ModelType::suziFlatN), lambSp);
	suziFlatO->setRotation(0.02f, glm::vec3(.0f, 1.0f, .0f));
	MatrixHandler::translate(suziFlatO->getMatRef(), glm::vec3(5.0f, 0.0f, 2.0f));

	Object* suziSmoothO = new Object(ModelFactory::premade(ModelType::suziSmoothN), phongSp);
	suziSmoothO->setRotation(-0.02f, glm::vec3(.0f, 1.0f, .0f));
	MatrixHandler::translate(suziSmoothO->getMatRef(), glm::vec3(5.0f, 0.0f, 8.0f));


	Camera* camera = new Camera(window->getWidth(), window->getHeight(), glm::vec3(0.0f, 0.0f, 20.0f));
	camera->attach(constSp);
	camera->attach(colSp);
	camera->attach(lambSp);
	camera->attach(phongSp);


	Scene* testScene = new Scene(sceneSeq); sceneSeq += 1;	
	testScene->addObject(cube);
	testScene->addObject(roof);
	testScene->addObject(sphereO);
	testScene->addObject(plainO);
	testScene->addObject(suziFlatO);
	testScene->addObject(suziSmoothO);
	testScene->addCamera(camera);
	scenes.push_back(testScene);
	
	Scene* scenaNemca = new Scene(sceneSeq); sceneSeq += 1;
	Model* sphereM = ModelFactory::premade(ModelType::sphereN);
	Object* sphereO1 = new Object(sphereM, phongSp);
	MatrixHandler::translate(sphereO1->getMatRef(), glm::vec3(-2.5f, 0.0f, 0.0f));
	Object* sphereO2 = new Object(sphereM, phongSp);
	MatrixHandler::translate(sphereO2->getMatRef(), glm::vec3(2.5f, 0.0f, 0.0f));
	Object* sphereO3 = new Object(sphereM, phongSp);
	MatrixHandler::translate(sphereO3->getMatRef(), glm::vec3(0.0f, 2.5f, 0.0f));
	Object* sphereO4 = new Object(sphereM, phongSp);
	MatrixHandler::translate(sphereO4->getMatRef(), glm::vec3(0.0f, -2.5f, 0.0f));

	sphereO1->setColor(glm::vec3(.1f, .1f, .9f));
	sphereO2->setColor(glm::vec3(.1f, .1f, .9f));
	sphereO3->setColor(glm::vec3(.1f, .1f, .9f));
	sphereO4->setColor(glm::vec3(.1f, .1f, .9f));


	scenaNemca->addObject(sphereO1);
	scenaNemca->addObject(sphereO2);
	scenaNemca->addObject(sphereO3);
	scenaNemca->addObject(sphereO4);
	scenaNemca->setLightPos(glm::vec3(.0f, .0f, .0f));
	scenaNemca->addCamera(camera);
	scenes.push_back(scenaNemca);


	Scene* forest = new Scene(sceneSeq); sceneSeq += 1;
	srand(time(NULL));
	int probability1 = rand() % 100 + 1;
	int probability2 = rand() % 100 + 1;
	int probability3 = rand() % 100 + 1;

	Object* forestGround = new Object(ModelFactory::premade(ModelType::plainN), constSp);
	forestGround->setColor(glm::vec3(float(85) / float(255), float(81) / float(255), float(66) / float(255)));
	MatrixHandler::scale(forestGround->getMatRef(), glm::vec3(50.0f, 1.0f, 50.0f));
	forest->addObject(forestGround);
	Model* giftM = ModelFactory::premade(ModelType::giftN);
	Model* bushM = ModelFactory::premade(ModelType::bushN);
	Model* treeM = ModelFactory::premade(ModelType::treeN);
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			Object* leafy;
			if (probability3 > 90) {
				leafy = new Object(giftM, constSp);
			}
			else if (probability3 > 50) {
				leafy = new Object(bushM, phongSp);
				leafy->setColor(glm::vec3(float(18) / float(255), float(230) / float(255), float(3) / float(255)));
			}
			else{
				leafy = new Object(treeM, phongSp);
				leafy->setColor(glm::vec3(float(22) / float(255), float(96) / float(255), float(55) / float(255)));
			}
			forest->addObject(leafy);
			MatrixHandler::translate(leafy->getMatRef(), glm::vec3(float(i / 5) + float(probability1 / 3), 0.0f, float(j / 5) + float(probability2 / 3)));
			probability1 = rand() % 100 + 1;
			probability2 = rand() % 100 + 1;
			probability3 = rand() % 100 + 1;
		}
	forest->setLightPos(glm::vec3(.0f, 30.0f, .0f));
	forest->addCamera(camera);
	scenes.push_back(forest);
	}
}
void Engine::startRendering() {

	currentScene = scenes.front();
	glEnable(GL_DEPTH_TEST);

	currentScene->getCurrentCam()->notify();
	while (!glfwWindowShouldClose(this->window->getGLFWWindow())) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//currentScene->getCurrentCam()->UpdateShader(sp->getShaderProgram());
		currentScene->draw(deltaTime);
		processHeldKeys();

	// update other events like input handling
		glfwPollEvents();
	// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(this->window->getGLFWWindow());
	}

glfwDestroyWindow(this->window->getGLFWWindow());
glfwTerminate();
exit(EXIT_SUCCESS);
}

Window* Engine::getWindow() {
	return this->window;
}
void Engine::nextScene() {
	GLint nextSeq = this->currentScene->sceneSeq + 1;
	if (nextSeq > scenes.size()+1)
		nextSeq = 0;
	this->currentScene = scenes.at(nextSeq);
}
void Engine::onClick(int button, int action, double x, double y) {
	/*if (action == GLFW_PRESS) {
		printf("press %d %d %f %f\n", button, action, x, y);
	}
	if (action == GLFW_RELEASE) {
		printf("release %d %d %f %f\n", button, action, x, y);
	}*/
	return;
}
void Engine::onKey(int key, int scancode, int action, int mods) {
	/*if (action == GLFW_PRESS) {
		printf("press %d %d %d %d\n", key, scancode, action, mods);
	}
	if (action == GLFW_RELEASE) {
		printf("release %d %d %d %d\n", key, scancode, action, mods);
	}*/
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
		printf("Zaviram\n");
		glfwSetWindowShouldClose(window->getGLFWWindow(), GLFW_TRUE);
	}
	if (action == GLFW_PRESS && key == GLFW_KEY_N) {
		this->nextScene();
	}
	return;
}
void Engine::onMove(double x, double y) {
	printf("move %f %f \n", x, y);
	double xmove, ymove;
	xmove = x - (window->getWidth() / 2);
	ymove = y - (window->getHeight() / 2);

	glfwSetCursorPos(window->getGLFWWindow(), (window->getWidth() / 2), (window->getHeight() / 2));

	this->currentScene->getCurrentCam()->rotate(xmove, ymove);

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
		currentScene->getCurrentCam()->move(Camera_Movement::CAM_FORWARD);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->move(Camera_Movement::CAM_LEFT);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->move(Camera_Movement::CAM_BACKWARD);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->move(Camera_Movement::CAM_RIGHT);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->move(Camera_Movement::CAM_UP);
	}
	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		currentScene->getCurrentCam()->move(Camera_Movement::CAM_DOWN);
	}
}