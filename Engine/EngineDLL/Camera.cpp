#include "Camera.h"

Camera::Camera(Renderer * renderer) : Component(renderer){
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
	pos = glm::translate(glm::mat4(1.0f), (glm::vec3)((right * xAxis)+(forward * zAxis))) * pos;

	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}

void Camera::Yaw(float xAxis) {

	forward = glm::rotate(glm::mat4(1.0f), xAxis, glm::vec3(up.x, up.y, up.z)) * forward;
	right = glm::rotate(glm::mat4(1.0f), xAxis, glm::vec3(up.x, up.y, up.z)) * right;
	
	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,															
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}

void Camera::Pitch(float yAxis) {

	forward = glm::rotate(glm::mat4(1.0f), yAxis, glm::vec3(right.x, right.y, right.z)) * forward;
	up = glm::rotate(glm::mat4(1.0f), yAxis, glm::vec3(right.x, right.y, right.z)) * up;

	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}

void Camera::Roll(float zAxis) {

	right = glm::rotate(glm::mat4(1.0f), zAxis, glm::vec3(forward.x, forward.y, forward.z)) * right;
	up = glm::rotate(glm::mat4(1.0f), zAxis, glm::vec3(forward.x, forward.y, forward.z)) * up;

	ViewMatrix = glm::lookAt(
		(glm::vec3)pos,
		(glm::vec3)(pos + forward),
		(glm::vec3)up
	);

	render->ModifyCamera(ViewMatrix);
}