#ifndef MESH_H
#define MESH_H
#include "Shape.h"
#include "Material.h"
#include "Importer.h"

struct MeshInfo {
	unsigned int bufferId;
	unsigned int textureBufferId;
	unsigned int indexBufferId;
	bool shouldDispose;
	bool shouldDisposeTexture;
	bool shouldDisposeIndices;
	int vtxCount;
	int vtxTextureCount;
	int idxCount;
	float* vertex;
	float* textureVertex;
	unsigned int * indices;
};

class ENGINEDLL_API Mesh : public Shape {

	Header header;

	std::vector<MeshInfo>* meshInfo;
	std::vector<MeshEntry>* mesh;

	unsigned int textureId;
	
public:
	Mesh(Renderer * renderer, const std::string& name);
	~Mesh() { /*DisposeIndex();*/ };

	void LoadMaterial(const char * name);

	void SetVertices(MeshInfo& mesh);
	void SetTextureVertices(MeshInfo& mesh);
	void SetIndexVertices(MeshInfo& mesh);

	void DisposeVertices(bool shouldDispose, unsigned int bufferId);
	void DisposeTextures(bool shouldDisposeTexture, unsigned int textureBufferId);
	void DisposeIndex(bool shouldDisposeIndices, unsigned int indexBufferId);

	void Draw();
};
#endif