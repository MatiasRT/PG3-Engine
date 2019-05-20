#include "Importer.h"


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

void Importer::LoadMesh(const std::string& name, std::vector<MeshEntry> * mesh) {
	// Release the previously loaded mesh (if it exists)
	//Clear();

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(name, ASSIMP_LOAD_FLAGS);

	if (pScene) {
		//Ret = InitFromScene(pScene, name);
		//InitFromScene(pScene, name);
		mesh->resize(pScene->mNumMeshes);

		// Initialize the meshes in the scene one by one
		for (unsigned int i = 0; i < mesh->size(); i++) {
			const aiMesh* paiMesh = pScene->mMeshes[i];
			InitMesh(i, paiMesh, mesh->at(i));
		}
	}
	else {
		printf("Error parsing '%s': '%s'\n", name, Importer.GetErrorString());
	}
}

void Importer::InitMesh(unsigned int index, const aiMesh * paiMesh, MeshEntry& mesh) {

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	mesh.vertices = new std::vector<float>();
	mesh.texture = new std::vector<float>();
	mesh.indices = new std::vector<unsigned int>();

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		mesh.vertices->push_back(pPos->x);
		mesh.vertices->push_back(pPos->y);
		mesh.vertices->push_back(pPos->z);
		
		mesh.texture->push_back(pTexCoord->x);
		mesh.texture->push_back(pTexCoord->y);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		mesh.indices->push_back(Face.mIndices[0]);
		mesh.indices->push_back(Face.mIndices[1]);
		mesh.indices->push_back(Face.mIndices[2]);
	}
}