#include "GameNode.h"

GameNode::GameNode(Renderer * render) {
	renderer = render;
	nodeChild = new std::list<GameNode*>();
	components = new std::list<Component>();
}

GameNode::~GameNode() {

}

void GameNode::AddChild(GameNode* node) {
	nodeChild->push_back(node);
}

void GameNode::AddComponent(Component comp) {
	components->push_back(comp);
}

void GameNode::RemoveChild(int index) {
	int i = 0;
	for (std::list<GameNode*>::iterator it = nodeChild->begin(); it != nodeChild->end(); it++) {
		i++;
		if (i == index) {
			nodeChild->erase(it);
			break;
		}
	}
}

void GameNode::RemoveComponent(int index) {
	int i = 0;
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); it++) {
		i++;
		if (i == index) {
			components->erase(it);
			break;
		}
	}
}

Component GameNode::GetComponent(ComponentsType type) {
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); it++) {
		if (it->type == type)
			return *it;
	}
	return Component(renderer);
}

void GameNode::Update(float deltaTime, glm::mat4 vMatrix) {
	ViewMatrix *= renderer->GetViewMatrix();

	for(std::list<Component>::iterator it = components->begin(); it != components->end(); it++){
		it->Update(deltaTime, ViewMatrix);
	}

	for (std::list<GameNode*>::iterator it = nodeChild->begin(); it != nodeChild->end(); it++) {
		(*it)->Update(deltaTime, renderer->GetViewMatrix());
	}
	renderer->SetViewMatrix(ViewMatrix);
}

void GameNode::Draw() {

	for (std::list<Component>::iterator it = components->begin(); it != components->end(); it++) {
		it->Draw();
	}

	for (std::list<GameNode*>::iterator it = nodeChild->begin(); it != nodeChild->end(); it++) {
		(*it)->Draw();
	}
}