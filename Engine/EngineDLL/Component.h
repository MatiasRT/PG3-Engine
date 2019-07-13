#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include "Exports.h"
#include "Definitions.h"
#include "Material.h"
#include "Entity.h"
#include<glm\gtc\matrix_transform.hpp>
#include<glm\glm.hpp>

class ENGINEDLL_API Component : public Entity {
public:

	ComponentsType type;

	Component(Renderer * renderer);
	~Component();
	
	void Update(float deltaTime, glm::mat4 ViewMatrix);
	void Draw();

	//ComponentsType GetComponentType() { return type; }
};
#endif