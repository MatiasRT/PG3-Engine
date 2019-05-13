#pragma once
#include <assimp/postprocess.h>
#define GL_TRIANGLES			0x0004
#define GL_TRIANGLE_STRIP		0x0005
#define GL_TRIANGLE_FAN			0x0006
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

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