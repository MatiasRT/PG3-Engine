#ifndef MESH_H
#define MESH_H
#include "Importer.h"
#include "Component.h"
#include "GameNode.h"

struct MeshInfo {
	unsigned int bufferId;
	unsigned int textureBufferId;
	unsigned int indexBufferId;
	unsigned int textureId;
	bool shouldDispose;
	bool shouldDisposeIndices;
	bool shouldDisposeTexture;
	unsigned int vtxCount;
	unsigned int textureCount;
	unsigned int idxCount;
	float * vertex;
	float * textureVertex;
	unsigned int * indices;
	Material * material;
	unsigned int programId;
};

class ENGINEDLL_API Mesh : public Component {
	Header header;

	unsigned int textureId;

	MeshInfo* meshInfo;
	const char* textureFile;
	MeshData* meshData;

	void SetTextureVertex();
	void SetIndexVertex();
	void SetVertices();
	void DisposeIndex();
	void DisposeTexture();
public:
	Mesh(Renderer * renderer, const char* txtFile);
	~Mesh();

	void SetMeshData(MeshData * meshD);
	void LoadMaterial(const char * bmpFile, unsigned int &textureId, Material * material);
	void Draw() override;
	
	MeshData * GetMeshData() { return meshData; };
};
#endif