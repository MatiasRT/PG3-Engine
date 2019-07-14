#include "Mesh.h"

Mesh::Mesh(Renderer * renderer, const char * txtFile) : Component(renderer) {
	type = ComponentsType::MeshRenderType;
	textureFile = txtFile;
	meshInfo = new MeshInfo;
	meshData = new MeshData();
	//Importer::LoadMesh(fbxFile,textureFile, rootNode, render);
	//for (size_t i = 0; i < mesh->size(); i++) {
	meshInfo->shouldDispose = false;
	meshInfo->shouldDisposeIndices = false;
	meshInfo->shouldDisposeTexture = false;

	meshInfo->bufferId = -1;
	meshInfo->textureBufferId = -1;
	meshInfo->indexBufferId = -1;
}

void Mesh::SetMeshData(MeshData * meshD) {
	meshData = meshD;
	meshInfo->vtxCount = meshData->vertices->size();
	meshInfo->idxCount = meshData->indices->size();
	meshInfo->textureCount = meshData->textures->size();

	meshInfo->vertex = new float[meshInfo->vtxCount];
	for (size_t j = 0; j < meshInfo->vtxCount; j++) {
		meshInfo->vertex[j] = meshData->vertices->at(j);
	}
	SetVertices();

	meshInfo->textureVertex = new float[meshInfo->textureCount];
	for (size_t j = 0; j < meshInfo->textureCount; j++) {
		meshInfo->textureVertex[j] = meshData->textures->at(j);
	}
	SetTextureVertex();

	meshInfo->indices = new unsigned int[meshInfo->idxCount];
	for (size_t j = 0; j < meshInfo->idxCount; j++) {
		meshInfo->indices[j] = meshData->indices->at(j);
	}
	SetIndexVertex();

	meshInfo->material = new Material();
	meshInfo->programId = meshInfo->material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	LoadMaterial(textureFile, meshInfo->textureId, meshInfo->material);

}

void Mesh::LoadMaterial(const char * bmpFile, unsigned int &textureId, Material * material) {
	header = Importer::LoadBMP(bmpFile);
	textureId = renderer->UploadData(header.width, header.height, header.data);
	material->BindTexture();
}

void Mesh::SetVertices() {

	meshInfo->shouldDispose = true;
	meshInfo->bufferId = renderer->GenBuffer(meshInfo->vertex, sizeof(float)* meshInfo->vtxCount);
}

void Mesh::SetTextureVertex() {
	DisposeTexture();

	meshInfo->shouldDisposeTexture = true;
	meshInfo->textureBufferId = renderer->GenBuffer(meshInfo->textureVertex, sizeof(float)* meshInfo->textureCount);
}

void Mesh::SetIndexVertex() {
	DisposeIndex();

	meshInfo->shouldDisposeIndices = true;
	meshInfo->indexBufferId = renderer->GenElementBuffer(meshInfo->indices, sizeof(int)* meshInfo->idxCount);
}

void Mesh::DisposeIndex() {

}

void Mesh::DisposeTexture() {

}

void Mesh::Draw() {
	
	if (meshInfo->material != NULL) {
		meshInfo->material->Bind();
		meshInfo->material->SetMatrixProperty(renderer->GetWVP());
	}
	renderer->BindTexture(meshInfo->textureId, meshInfo->textureBufferId);
	renderer->BeginDraw(0);																									// Le decimos al renderer que comience a dibujar
	renderer->BeginDraw(1);
	renderer->BindBuffer(meshInfo->bufferId, 0);																			// Unimos el buffer con el buffer binding point
	renderer->BindBuffer(1, meshInfo->textureBufferId, 2);
	renderer->DrawElementBuffer(meshInfo->idxCount, meshInfo->indexBufferId);									// El renderer dibuja el triangulo
	renderer->EndDraw(0);																									// Deja de dibujar
	renderer->EndDraw(1);
}

Mesh::~Mesh() {
	delete[] meshInfo->vertex;
	delete[] meshInfo->textureVertex;
	delete[] meshInfo->indices;
	delete meshInfo->material;
	delete meshInfo;
	delete meshData;
}