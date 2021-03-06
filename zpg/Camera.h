#pragma once
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "Utilities/ISubject.h"
#include <vector>
#include"Shaders/ShaderProg.h"
#include"ReflectorLight.h"

const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

enum class Camera_Movement {
	CAM_FORWARD,
	CAM_BACKWARD,
	CAM_LEFT,
	CAM_RIGHT,
	CAM_UP,
	CAM_DOWN
};

class Camera : public ISubject
{
private:
	glm::vec3 position;
public:
	glm::mat4 viewMat;
	std::vector<IObserver*> observers;
	std::vector<IPositionObserver*> posObservers;
	// Stores the main vectors of the camera
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 projMat;
	GLfloat movementSpeed;
	GLfloat sensitivity = 0.05f;
	GLfloat pitch;
	GLfloat yaw;
	ReflectorLight flashlight;
	GLboolean flashOn;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	void updateShader(ShaderProg* shaderProg);
	void calcOrientation();
	void calcView();
	void calcProjection(GLint width, GLint height);
	void move(Camera_Movement direction);
	void rotate(double xoffset, double yoffset, GLboolean constrainPitch = true);
	void toggleFlashlight();
	virtual void attach(IObserver* observer) override;
	virtual void detach(IObserver* observer) override;
	virtual void attach(IPositionObserver* observer) override;
	virtual void detach(IPositionObserver* observer) override;
	virtual void notify() override;

};