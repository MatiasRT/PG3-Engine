#include "Camera.h"

Camera::Camera(Renderer * renderer) {
	render = renderer;
}

void Camera::Walk(float xAxis, float zAxis) {
	render->TranslateCamera(glm::vec3(xAxis, 0, zAxis));
}

void Camera::Yaw(float xAxis) {

	glm::vec3 rot = glm::vec3(xAxis, 0, 0);

	render->RotateCamera(rot);
}

void Camera::Pitch(float yAxis) {

	glm::vec3 rot(0, yAxis, 0);


	render->RotateCamera(rot);
}

void Camera::Roll(float zAxis) {

	glm::vec3 rot(0, 0, zAxis);

	render->RotateCamera(rot);

}