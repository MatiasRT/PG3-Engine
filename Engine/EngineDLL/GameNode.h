#pragma once
#ifndef GAMENODE_H
#define GAMENODE_H
#include "Renderer.h"
#include "Exports.h"
#include "Component.h"
#include "Definitions.h"
#include <list>
using namespace std;

class ENGINEDLL_API GameNode : public Entity {
	Renderer * renderer;

	vector<Component*>* components;
	vector<GameNode*>* nodes;
public:
	GameNode(Renderer * render);
	~GameNode() { };
	void AddComponent(Component * comp);
	void RemoveComponent(int index);
	Component* GetComponent(int index);
	Component* GetComponent(ComponentsType type);
	void RemoveChild(int index);
	void AddChild(GameNode * node);
	vector<GameNode*>* GetChilds();
	vector<Component*>* GetComponents();

	GameNode * GetNode(int index);
	void Update();
	void Draw();
};
#endif