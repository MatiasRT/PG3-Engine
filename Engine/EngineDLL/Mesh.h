#pragma once
#include "Shape.h"
#include "Material.h"

class ENGINEDLL_API Mesh : public Shape {
protected:
	unsigned int bufferId;
	unsigned int colorBufferId;
	unsigned int indexBufferId;
	bool shouldDispose;
	bool shouldDisposeColor;
	bool shouldDisposeIndices;
	int vtxCount;
	int vtxColorCount;
	int idxCount;
	float* vertex;
	float* colorVertex;
	unsigned int * indices;

	Material * material;
public:
	Mesh(Renderer * renderer);
	~Mesh() { DisposeIndex(); };
	void SetIndexVertices(unsigned int* indices, int count);
	void DisposeIndex();
	void Draw();
};