#ifndef IMPORTER_H
#define IMPORTER_H
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)
#include "Exports.h"
#include "Definitions.h"
#include <fstream>
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assert.h"
#include "assimp/postprocess.h"

struct Header {
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
};

static class ENGINEDLL_API Importer {

	static void InitMesh(unsigned int index, const aiMesh * paiMesh, MeshEntry& mesh);

public:

	static Header LoadBMP(const char * name);
	static bool CheckFormat(const char * name, unsigned char header[], FILE * file);

	static void LoadMesh(const std::string& name, std::vector<MeshEntry> * mesh);
};
#endif