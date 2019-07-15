#include "Collider.h"

Collider::Collider(Renderer * render) {
	renderer = render;
}

glm::vec3 Collider::GetVertices(int index) {
	glm::vec4 globalRotatedPos(collider[index].x, collider[index].y, collider[index].z, 1.0f);

	globalRotatedPos = renderer->GetWorldMatrix() * globalRotatedPos;

	return (glm::vec3)globalRotatedPos;
}

void Collider::SetVertices(glm::vec3 col[8]) {
	for (int i = 0; i < 8; i++)
		collider[i] = col[i];
}