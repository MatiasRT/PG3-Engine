#include "GameNode.h"

GameNode::GameNode(Renderer * render) : Entity(render) {
	cout << "Node" << endl;
	renderer = render;
	worldMatrix = renderer->GetViewMatrix();
	nodes = new vector<GameNode*>();
	components = new vector<Component*>();
}

void GameNode::AddComponent(Component * comp) {
	components->push_back(comp);
}

Component * GameNode::GetComponent(ComponentsType type) {
	for (size_t i = 0; i < components->size(); i++) {
		if (components->at(i)->type == type)
			return components->at(i);
	}
}

void GameNode::RemoveComponent(int index) {
	int i = 0;
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) {
		if (i == index) {
			components->erase(it);
			break;
		}
		i++;
	}
}

Component * GameNode::GetComponent(int index) {
	if (index > components->size())
		return components->at(components->size() - 1);
	return components->at(index);
}

void GameNode::RemoveChild(int index) {
	int i = 0;
	for (vector<GameNode*>::iterator it = nodes->begin(); it != nodes->end(); ++it) {
		if (i == index) {
			nodes->erase(it);
			break;
		}
		i++;
	}
}

void GameNode::AddChild(GameNode * node) {
	nodes->push_back(node);
}

vector<GameNode*>* GameNode::GetChilds() {
	if (nodes == nullptr || nodes->size() == 0)
		return nullptr;
	return nodes;
}

vector<Component*>* GameNode::GetComponents() {
	return components;
}

GameNode * GameNode::GetNode(int index) {
	if (index >= nodes->size())
		return nodes->at(nodes->size() - 1);
	return nodes->at(index);
}

void GameNode::Update() {
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) {
		(*it)->Update();
	}

	for (vector<GameNode*>::iterator it = nodes->begin(); it != nodes->end(); ++it) {
		(*it)->Update();
	}
}

void GameNode::Draw() {
	//me guardo la MVP anterior
	glm::mat4 actualWM = renderer->GetWorldMatrix();
	glm::mat4 actualVM = renderer->GetViewMatrix();
	glm::mat4 actualPM = renderer->GetProjectionMatrix();

	//multiplico
	renderer->SetWorldMatrix(actualWM * worldMatrix);

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) {
		(*it)->Draw();
	}
	for (vector<GameNode*>::iterator it = nodes->begin(); it != nodes->end(); ++it) {
		(*it)->Draw();
	}

	//las vuelvo a setear
	renderer->SetViewMatrix(actualVM);
	renderer->SetWorldMatrix(actualWM);
	renderer->SetProjectionMatrix(actualPM);
}