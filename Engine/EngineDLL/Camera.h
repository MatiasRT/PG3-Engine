#pragma once
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Exports.h"
#include "Entity.h"
#include "Renderer.h"
#include "Component.h"

using namespace std;
class ENGINEDLL_API Camera : public Component {
	
	Renderer* render;
	glm::mat4 ViewMatrix;
	glm::vec4 forward;
	glm::vec4 right;
	glm::vec4 up;
	glm::vec4 pos;

public:
	Camera(Renderer * renderer);
	~Camera() {};
	
	void Walk(float xAxis, float zAxis);
	void Yaw(float xAxis);
	void Pitch(float yAxis);
	void Roll(float zAxis);
};