#include "Camera.h"

Camera::Camera(Renderer * renderer) {
	forward = glm::vec4(0, 0, 1, 0);
	right = glm::vec4(1, 0, 0, 0);
	up = glm::vec4(0, 1, 0, 0);

	pos = glm::vec4(0, 0, 0, 1);

	render = renderer;
	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);
}

void Camera::Walk(float xAxis, float zAxis) {
	pos = glm::translate(glm::mat4(1.0f), glm::vec3(xAxis, 0, zAxis)) * pos;

	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}

void Camera::Yaw(float xAxis) {

	forward = glm::rotate(glm::mat4(1.0f), xAxis, glm::vec3(0.0f, 1.0f, 0.0f)) * forward;
	right = glm::rotate(glm::mat4(1.0f), xAxis, glm::vec3(0.0f, 1.0f, 0.0f)) * right;
	
	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,															
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}

void Camera::Pitch(float yAxis) {

	forward = glm::rotate(glm::mat4(1.0f), yAxis, glm::vec3(1.0f, 0.0f, 0.0f)) * forward;
	up = glm::rotate(glm::mat4(1.0f), yAxis, glm::vec3(1.0f, 0.0f, 0.0f)) * up;

	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}

void Camera::Roll(float zAxis) {

	right = glm::rotate(glm::mat4(1.0f), zAxis, glm::vec3(0.0f, 0.0f, 1.0f)) * right;
	up = glm::rotate(glm::mat4(1.0f), zAxis, glm::vec3(0.0f, 0.0f, 1.0f)) * up;

	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}