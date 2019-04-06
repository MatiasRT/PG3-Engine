#include "Camera.h"


Camera::Camera(Renderer * renderer) {
	render = renderer;
}

void Camera::Walk(float xAxis, float zAxis) {
	render->TranslateCamera(glm::vec3(xAxis, 0, zAxis));
}

void Camera::Yaw(float xAxis) {
	render->YawCamera(glm::vec3(xAxis, 0, 0));
}

void Camera::Pitch(float xAxis, float yAxis) {
	render->PitchCamera(glm::vec3(xAxis, yAxis, 0));
}