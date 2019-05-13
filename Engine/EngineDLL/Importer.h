#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <fstream>
struct Header {
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
};
static class ENGINEDLL_API Importer {
public:
	static Header LoadBMP(const char * name);
	static bool CheckFormat(const char * name, unsigned char header[], FILE * file);

	static bool LoadMesh(const char * name);
};