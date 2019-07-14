#include "Importer.h"
#include "Mesh.h"

Header Importer::LoadBMP(const char * name) {

	// Lectura de información del encabezado del archivo
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	FILE * file;
	fopen_s(&file, name, "rb");
	Header h;

	if (CheckFormat(name, header, file)) {
		// Lectura de los enteros desde el arreglo de bytes
		h.dataPos = *(int*)&(header[0x0A]);
		h.imageSize = *(int*)&(header[0x22]);
		h.width = *(int*)&(header[0x12]);
		h.height = *(int*)&(header[0x16]);
	}

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (h.imageSize == 0)    
		h.imageSize = h.width * h.height * 3;	// 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (h.dataPos == 0)      
		h.dataPos = 54;						// El encabezado del BMP está hecho de ésta manera

	// Se crea un buffer
	h.data = new unsigned char[h.imageSize];

	// Leemos la información del archivo y la ponemos en el buffer
	fread(h.data, 1, h.imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
	fclose(file);

	return h;
}

bool Importer::CheckFormat(const char * name, unsigned char header[], FILE * file) {

	if (!file) {
		printf("Image could not be opened\n"); 
		return 0; 
	}

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}


}

void Importer::LoadMesh(const char * fbxFile, const char * txtFile, GameNode * father, Renderer * renderer) {
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* pScene = importer.ReadFile(fbxFile, ASSIMP_LOAD_FLAGS);

	// If the import failed, report it
	if (!pScene) {
		return;
	}
	if (!pScene->HasMeshes()) {
		return;
	}
	
	ProcessNodes(txtFile, father, pScene->mRootNode, pScene, renderer);
}

void Importer::ProcessNodes(const char * txtFile, GameNode* father, aiNode* node, const aiScene* scene, Renderer* renderer) {
	for (int i = 0; i < (int)node->mNumMeshes; i++) {
		Mesh * mesh = new Mesh(renderer, txtFile);
		InitMesh(scene->mMeshes[node->mMeshes[i]], mesh);
		GameNode * child = new GameNode(renderer);
		child->AddComponent((Component*)mesh);
		father->AddChild(child);
	}

	for (int i = 0; i < (int)node->mNumChildren; i++) {
		ProcessNodes(txtFile, father, node->mChildren[i], scene, renderer);
	}
}

void Importer::InitMesh(const aiMesh* paiMesh, Mesh * mesh) {
	MeshData * meshD = mesh->GetMeshData();
	meshD->vertices = new std::vector<float>();
	meshD->textures = new std::vector<float>();
	meshD->indices = new std::vector<unsigned int>();

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		meshD->vertices->push_back(pPos->y);
		meshD->vertices->push_back(pPos->x);
		meshD->vertices->push_back(pPos->z);
		meshD->textures->push_back(pTexCoord->x);
		meshD->textures->push_back(pTexCoord->y);

	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		meshD->indices->push_back(Face.mIndices[0]);
		meshD->indices->push_back(Face.mIndices[1]);
		meshD->indices->push_back(Face.mIndices[2]);
	}

	mesh->SetMeshData(meshD);
}