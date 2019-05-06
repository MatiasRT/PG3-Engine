#include "Mesh.h"

Mesh::Mesh(Renderer * renderer) : Shape(renderer){
	shouldDispose = false;
	shouldDisposeColor = false;
	shouldDisposeIndices = false;
	
	bufferId = -1;
	colorBufferId = -1;
	indexBufferId = -1;

	vtxCount = 8;
	vtxColorCount = 8;
	idxCount = 12;

	vertex = new float[vtxCount * 3]{
																// front
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
																// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0
	};
	SetVertices(vertex, vtxCount);

	colorVertex = new float[vtxColorCount * 3]{
																// front colors
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
																// back colors
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 1.0, 1.0
	};
	SetColorVertices(colorVertex, vtxColorCount);

	indices = new unsigned int[idxCount * 3]{
																// front
		0, 1, 2,
		2, 3, 0,
																// top
		1, 5, 6,
		6, 2, 1,
																// back
		7, 6, 5,
		5, 4, 7,
																// bottom
		4, 0, 3,
		3, 7, 4,
																// left
		4, 5, 1,
		1, 0, 4,
																// right
		3, 2, 6,
		6, 7, 3,
	};
	SetIndexVertices(indices, idxCount);
}

void Mesh::SetIndexVertices(unsigned int * indices, int count) {
	DisposeIndex();

	idxCount = count;
	shouldDisposeIndices = true;
	//indexBufferId = renderer->GenMeshBuffer(indices, sizeof(int) * indexCount * 3);
	indexBufferId = renderer->GenElementBuffer(indices, sizeof(int) * idxCount * 3);
}

void Mesh::DisposeIndex() {
	if (shouldDisposeIndices) {
		renderer->DestroyBuffer(indexBufferId);
		shouldDisposeIndices = false;
	}
}

void Mesh::Draw() {
	DrawIndexMesh(indices, idxCount * 3, indexBufferId);
}