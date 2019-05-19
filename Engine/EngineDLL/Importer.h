#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <fstream>
#include <vector>
#include <assimp/mesh.h>

struct Header {
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
};
struct MeshEntry {
	std::vector<float>* vertices;
	std::vector<unsigned int>* indices;
	std::vector<float>* texture;
};

static class ENGINEDLL_API Importer {

	void InitMesh(unsigned int index, const aiMesh * paiMesh, MeshEntry mesh);

public:

	static Header LoadBMP(const char * name);
	static bool CheckFormat(const char * name, unsigned char header[], FILE * file);

	void LoadMesh(const std::string& name, std::vector<MeshEntry> * mesh);
};