#include "GameNode.h"

GameNode::GameNode(Renderer * render) {
	renderer = render;
}


GameNode::~GameNode() {

}

void GameNode::AddChild(GameNode node) {
	nodeChild->push_back(node);
}

void GameNode::AddComponent(Component comp) {
	components->push_back(comp);
}

void GameNode::RemoveChild(int index) {
	int i = 0;
	for (std::list<GameNode>::iterator it = nodeChild->begin(); it != nodeChild->end(); ++it) {
		i++;
		if (i == index) {
			nodeChild->erase(it);
			break;
		}
	}
}

void GameNode::RemoveComponent(int index) {
	int i = 0;
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it) {
		i++;
		if (i == index) {
			components->erase(it);
			break;
		}
	}
}

Component GameNode::GetComponent(ComponentsType type) {
	for (std::list<Component>::iterator it = components->begin(); it != components->end(); ++it) {
		if (it->GetComponentType() == type)
			return *it;
	}
	return Component(ComponentsType::NullComponentType);
}

void GameNode::Update(float deltaTime, glm::mat4 vMatrix) {
	ViewMatrix *= renderer->GetViewMatrix();

	for (std::list<GameNode>::iterator it = nodeChild->begin(); it != nodeChild->end(); ++it) {
		it->Update(deltaTime, renderer->GetViewMatrix());
	}
	renderer->SetViewMatrix(ViewMatrix);
}

void GameNode::Draw() {
	for (std::list<GameNode>::iterator it = nodeChild->begin(); it != nodeChild->end(); ++it) {
		it->Draw();
	}

	Component component = GetComponent(ComponentsType::MeshRenderType);
	if (component.GetComponentType() != ComponentsType::NullComponentType)
		component.Draw();
}