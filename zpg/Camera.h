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

const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

enum Camera_Movement {
	CAM_FORWARD,
	CAM_BACKWARD,
	CAM_LEFT,
	CAM_RIGHT,
	CAM_UP,
	CAM_DOWN
};

class Camera : public ISubject
{
public:
	std::vector<IObserver*> observers;
	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Right = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMat;
	glm::mat4 projMat;
	GLfloat MovementSpeed;
	GLfloat Sensitivity = 0.05f;
	GLfloat pitch;
	GLfloat yaw;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	void UpdateShader(GLuint shaderProg);
	void CalcOrientation();
	void CalcView();
	void Move(Camera_Movement direction);
	void Rotate(double xoffset, double yoffset, GLboolean constrainPitch = true);
	virtual void Attach(IObserver* observer) override;
	virtual void Detach(IObserver* observer) override;
	virtual void Notify() override;

};