//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>



static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

	float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
	};

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

int main(void)
{
	
	GLFWwindow* window;

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  



	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glewExperimental = GL_TRUE;
	glewInit();

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
	
	
	glfwSetErrorCallback(error_callback);
	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);


	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
/*
float points[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	+0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	+0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	+0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, +0.5f, 0.2f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	+0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	+0.5f, -0.5f, 0.2f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	+0.5f, +0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	+0.5f, +0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	+0.5f, -0.5f, 0.2f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	+0.5f, +0.5f, 0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, 0.0f, 0.0f, 0.2f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.2f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	+0.5f, -0.5f, 0.0f, 0.5f, 0.2f, 1.0f, 0.0f, 1.0f,
	+0.5f, -0.5f, 0.0f, 0.5f, 0.2f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.2f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	+0.5f, -0.5f, 0.2f, 0.0f, 0.2f, 0.0f, 1.0f, 0.0f,

	-0.5f, +0.5f, 0.0f, 0.0f, 0.2f, 0.7f, 0.1f, 0.0f,
	-0.5f, +0.5f, 0.2f, 0.5f, 0.0f, 0.1f, 0.1f, 0.0f,
	+0.5f, +0.5f, 0.0f, 0.5f, 0.2f, 0.1f, 0.1f, 1.0f,
	+0.5f, +0.5f, 0.0f, 0.5f, 0.2f, 0.1f, 0.1f, 1.0f,
	-0.5f, +0.5f, 0.2f, 0.5f, 0.0f, 0.1f, 0.1f, 0.0f,
	+0.5f, +0.5f, 0.2f, 0.0f, 0.2f, 0.7f, 0.1f, 0.0f,
};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec4 vc;"
"layout(location=2) in float use;"
"out vec4 oc;"
"out float otime;"
"out float ouse;"
"uniform mat4 rot;"
"uniform mat4 tra;"
"uniform float time;"
"void main () {"
"vec3 offset = vec3(vp.x, vp.y, vp.z);"
"     gl_Position = tra * rot * vec4 (offset, 1.0);"
"	  oc = vc;"
"	  otime = time;"
"	  ouse = use;"
"}";

const char* fragment_shader =
"#version 330\n"
"in vec4 oc;"
"in float otime;"
"in float ouse;"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4(((1.0 + sin(otime)) / 2) * ouse + oc.r * (1.0 - ouse), (1.0 - (1.0 + sin(otime)) / 2) * ouse + oc.g * (1.0 - ouse), ((1.0 + cos(otime)) / 2) * ouse, 1.0 + sin(otime) + oc.b * (1.0 - ouse));"
"}";
int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(7 * sizeof(float)));

	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		exit(0);
	}

	int location = glGetUniformLocation(shaderProgram, "rot");
	int tra = glGetUniformLocation(shaderProgram, "tra");
	int time = glGetUniformLocation(shaderProgram, "time");

	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glUniform1f(time, glfwGetTime());
		glBindVertexArray(VAO);
		// draw triangles
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::rotate(model, glm::radians(90.0f * (float)(i + j)), glm::vec3(1.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(100.0f * (float)glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
				glm::mat4 pos = glm::mat4(1.0f);
				pos = glm::translate(pos, glm::vec3(-0.5f + 1.0f * i, -0.5 + 1.0f * j, 0.0f));
				glUniformMatrix4fv(tra, 1, GL_FALSE, glm::value_ptr(pos));
				glDrawArrays(GL_TRIANGLES, 0, 30);
			}
		}
		//mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}*/