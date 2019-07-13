#pragma once
#ifndef GAMENODE_H
#define GAMENODE_H
#include "Renderer.h"
#include "Exports.h"
#include "Component.h"
#include "Definitions.h"
#include <list>
class ENGINEDLL_API GameNode {
	std::list<GameNode> * nodeChild;
	std::list<Component> * components;

	Renderer * renderer;

	glm::mat4 ViewMatrix;
public:
	GameNode(Renderer * render);
	~GameNode();

	void AddChild(GameNode node);
	void AddComponent(Component comp);

	void RemoveChild(int index);
	void RemoveComponent(int index);

	Component GetComponent(ComponentsType type);

	void Update(float deltaTime, glm::mat4 ViewMatrix);
	void Draw();
};
#endif