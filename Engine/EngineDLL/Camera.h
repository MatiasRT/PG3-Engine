#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Exports.h"
#include "Entity.h"
#include "Renderer.h"
class ENGINEDLL_API Camera {
	
	//glm::vec3 pos;
	Renderer* render;

public:
	Camera(Renderer * renderer);
	~Camera() {};
	
	void Walk(float xAxis, float zAxis);
	void Yaw(float xAxis);
	void Pitch(float xAxis, float yAxis);
	//void Strafe();
};

