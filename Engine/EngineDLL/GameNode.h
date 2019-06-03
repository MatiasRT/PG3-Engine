#pragma once
#ifndef GAMENODE_H
#define GAMENODE_H
#include "Exports.h"
#include "Component.h"
#include <list>
class ENGINEDLL_API GameNode {
	std::list<GameNode> * nodeChild;
	std::list<Component> * components;
public:
	GameNode();
	~GameNode();
	void Start();
	void AddComponent();
	void RemoveComponent();
	void AddChild();
	void RemoveChild();
	void Update();
	void Draw();
};
#endif