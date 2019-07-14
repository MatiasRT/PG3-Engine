#pragma once
#include <vector>
#define GL_TRIANGLES			0x0004
#define GL_TRIANGLE_STRIP		0x0005
#define GL_TRIANGLE_FAN			0x0006

enum Layers {
	Player_layer = 0,
	Enemy_layer,
	Bullet_layer,
	EnemyBullet_layer,
	Tiles_layer,
	ObjectTile_layer,
	Count
};

enum Directions {
	Up,
	Down,
	Left,
	Right
};

enum CameraType {
	ortho,
	perspective
};

struct MeshData {
	std::vector<float>* vertices;
	std::vector<unsigned int>* indices;
	std::vector<float>* textures;
};

enum ComponentsType {
	MeshRenderType = 0,
	CamerasType,
	ColliderType,
	ScriptType,
	TransformType,
	NullComponentType
};