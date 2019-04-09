#include "Camera.h"

Camera::Camera(Renderer * renderer) {
	render = renderer;
	ViewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

void Camera::Walk(float xAxis, float zAxis) {
	ViewMatrix = glm::translate(ViewMatrix, glm::vec3(xAxis, 0, zAxis));
	//render->TranslateCamera(glm::vec3(xAxis, 0, zAxis));
	render->TranslateCamera(ViewMatrix);
}

void Camera::Yaw(float xAxis) {

	//glm::vec3 rot = glm::vec3(xAxis, 0, 0);
	ViewMatrix = glm::rotate(ViewMatrix, xAxis, glm::vec3(0.0f, 1.0f, 0.0f));

	render->RotateCamera(ViewMatrix);
}

void Camera::Pitch(float yAxis) {

	//glm::vec3 rot(0, yAxis, 0);
	ViewMatrix = glm::rotate(ViewMatrix, yAxis, glm::vec3(-1.0f, 0.0f, 0.0f));

	render->RotateCamera(ViewMatrix);
}

void Camera::Roll(float zAxis) {

	//glm::vec3 rot(0, 0, zAxis);
	ViewMatrix = glm::rotate(ViewMatrix, zAxis, glm::vec3(0.0f, 0.0f, 1.0f));

	render->RotateCamera(ViewMatrix);
}