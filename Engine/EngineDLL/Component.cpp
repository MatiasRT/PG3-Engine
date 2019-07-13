#include "Component.h"

Component::Component(Renderer * renderer) : Entity(renderer) {
	type = ComponentsType::NullComponentType;
}

Component::~Component() {

}

void Component::Update(float deltaTime, glm::mat4 ViewMatrix) {

}

void Component::Draw() {

}