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
		-1.0, -1.0,  1.0,										// frente
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
																
		-1.0, -1.0, -1.0,										// atras
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0
	};
	SetVertices(vertex, vtxCount);

	colorVertex = new float[vtxColorCount * 3]{															
		0.0, 0.0, 1.0,											// frente
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 1.0, 1.0,
																
		0.0, 0.0, 1.0,											// atras
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 1.0, 1.0
	};
	SetColorVertices(colorVertex, vtxColorCount);

	indices = new unsigned int[idxCount * 3]{
																
		0, 1, 2,												// frente
		2, 3, 0,
																
		1, 5, 6,												// superior
		6, 2, 1,
																
		7, 6, 5,												// atras
		5, 4, 7,
																
		4, 0, 3,												// inferior
		3, 7, 4,
																
		4, 5, 1,												// izquierda
		1, 0, 4,
																
		3, 2, 6,												// derecha
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