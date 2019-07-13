#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include "Exports.h"
#include "Definitions.h"
#include<glm\gtc\matrix_transform.hpp>
#include<glm\glm.hpp>

class ENGINEDLL_API Component {
	ComponentsType type;
public:
	Component(ComponentsType type);
	~Component();
	
	void Update(float deltaTime, glm::mat4 ViewMatrix);
	void Draw();

	ComponentsType GetComponentType() { return type; }
};
#endif