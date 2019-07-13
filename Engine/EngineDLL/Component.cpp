#include "Component.h"

Component::Component(ComponentsType _type) {
	type = _type;
}

Component::~Component() {

}

void Component::Update(float deltaTime, glm::mat4 ViewMatrix) {

}

void Component::Draw() {

}