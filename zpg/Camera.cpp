#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	position = position;
	yaw = -90.0f;
	pitch = 0.0f;
	movementSpeed = 0.1f;
	viewMat = glm::lookAt(position, position + orientation, worldUp);
	projMat = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	calcOrientation();
}

void Camera::updateShader(GLuint shaderProg) {
	GLint idViewMat = glGetUniformLocation(shaderProg, "viewMatrix");
	GLint idProjMat = glGetUniformLocation(shaderProg, "projectionMatrix");

	glUniformMatrix4fv(idViewMat, 1, GL_FALSE, &viewMat[0][0]);
	glUniformMatrix4fv(idProjMat, 1, GL_FALSE, &projMat[0][0]);

}
void Camera::calcOrientation() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	orientation = glm::normalize(front);
	// also re-calculate the right and up vector
	right = glm::normalize(glm::cross(orientation, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, orientation));
}
void Camera::calcView() {
	viewMat = glm::lookAt(position, position + orientation, worldUp);
	notify();
}
void Camera::move(Camera_Movement direction) {
	GLfloat velocity = movementSpeed;
	printf("direction %d\n", direction);
	switch (direction) {
	case CAM_FORWARD:
		position += orientation * velocity;
		break;
	case CAM_BACKWARD:
		position -= orientation * velocity;
		break;
	case CAM_LEFT:
		position -= right * velocity;
		break;
	case CAM_RIGHT:
		position += right * velocity;
		break;
	case CAM_UP:
		position += up * velocity;
		break;
	case CAM_DOWN:
		position -= up * velocity;
		break;	
	}
	calcView();
}
void Camera::rotate(double xoffset, double yoffset, GLboolean constrainPitch) {
	yaw += xoffset * sensitivity;
	pitch -= yoffset * sensitivity;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	calcOrientation();
	calcView();
}

//Observer functions

void Camera::attach(IObserver* observer)  {
	observers.push_back(observer);
}
void Camera::detach(IObserver* observer)  {
	auto iterator = std::find(observers.begin(), observers.end(), observer);

	if (iterator != observers.end()) { // observer found
		observers.erase(iterator); // remove the observer
	}
}
void Camera::notify()  {
	for (IObserver* observer : observers) { // notify all observers
		observer->update(viewMat, projMat, position);
	}
} 