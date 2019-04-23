#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Mesh : public Entity {
protected:
	unsigned int bufferId;
	unsigned int colorBufferId;
	bool shouldDispose;
	bool shouldDisposeColor;
	int vtxCount;
	int vtxColorCount;
	float* vertex;
	float* colorVertex;

	Material * material;
public:
	Mesh(Renderer * renderer);
	~Mesh() { Dispose(); DisposeColor(); };
	void SetVertices(float* vertex, int count);
	void SetColorVertices(float* vertex, int count);
	virtual void Draw() = 0;
	void DrawMesh(int type);
	void Dispose();
	void DisposeColor();
	void SetMaterial(Material* material);
};