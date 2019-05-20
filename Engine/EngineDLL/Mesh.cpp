#include "Mesh.h"

Mesh::Mesh(Renderer * renderer, const std::string& name) : Shape(renderer){

	mesh = new std::vector<MeshEntry>();
	meshInfo = new std::vector<MeshInfo>();

	Importer::LoadMesh(name, mesh);

	meshInfo->resize(mesh->size());

	for (int i = 0; i < mesh->size(); i++) {
		meshInfo->at(i).shouldDispose = false;
		meshInfo->at(i).shouldDisposeTexture = false;
		meshInfo->at(i).shouldDisposeIndices = false;

		meshInfo->at(i).bufferId = -1;
		meshInfo->at(i).textureBufferId = -1;
		meshInfo->at(i).indexBufferId = -1;

		meshInfo->at(i).vtxCount = mesh->at(i).vertices->size();
		meshInfo->at(i).vtxTextureCount = mesh->at(i).texture->size();
		meshInfo->at(i).idxCount = mesh->at(i).indices->size();

		meshInfo->at(i).vertex = new float[meshInfo->at(i).vtxCount];

		for (int j = 0; j < meshInfo->at(i).vtxCount; j++) 
			meshInfo->at(i).vertex[j] = mesh->at(i).vertices->at(j);
		
		SetVertices(meshInfo->at(i));


		meshInfo->at(i).textureVertex = new float[meshInfo->at(i).vtxTextureCount];

		for (int k = 0; k < meshInfo->at(i).vtxTextureCount; k++)
			meshInfo->at(i).textureVertex[k] = mesh->at(i).texture->at(k);

		SetTextureVertices(meshInfo->at(i));



		meshInfo->at(i).indices = new unsigned int[meshInfo->at(i).idxCount];

		for (int l = 0; l < meshInfo->at(i).idxCount; l++)
			meshInfo->at(i).indices[l] = mesh->at(i).indices->at(l);


		SetIndexVertices(meshInfo->at(i));
	}
}

void Mesh::LoadMaterial(const char * name) {

	header = Importer::LoadBMP(name);
	textureId = renderer->UploadData(header.width, header.height, header.data);
	material->BindTexture();
	
}

void Mesh::SetVertices(MeshInfo& mesh) {

	DisposeVertices(mesh.shouldDispose, mesh.bufferId);

	mesh.shouldDispose = true;

	mesh.bufferId = renderer->GenBuffer(mesh.vertex, sizeof(float) * mesh.vtxCount);
}

void Mesh::SetTextureVertices(MeshInfo & mesh) {

	DisposeTextures(mesh.shouldDisposeTexture, mesh.textureBufferId);

	mesh.shouldDisposeTexture = true;

	mesh.textureBufferId = renderer->GenBuffer(mesh.textureVertex, sizeof(float) * mesh.vtxTextureCount);
}

void Mesh::SetIndexVertices(MeshInfo & mesh) {
	DisposeIndex(mesh.shouldDisposeIndices, mesh.indexBufferId);

	mesh.shouldDisposeIndices = true;
	
	mesh.indexBufferId = renderer->GenElementBuffer(mesh.indices, sizeof(int) * mesh.idxCount);
}

void Mesh::DisposeVertices(bool shouldDispose, unsigned int bufferId) {
	if (shouldDispose) {
		renderer->DestroyBuffer(bufferId);
		shouldDispose = false;
	}
}

void Mesh::DisposeTextures(bool shouldDisposeTexture, unsigned int textureBufferId) {
	if (shouldDisposeTexture) {
		renderer->DestroyBuffer(textureBufferId);
		shouldDisposeTexture = false;
	}
}

void Mesh::DisposeIndex(bool shouldDisposeIndices, unsigned int indexBufferId) {
	if (shouldDisposeIndices) {
		renderer->DestroyBuffer(indexBufferId);
		shouldDisposeIndices = false;
	}
}

void Mesh::Draw() {

	for (int i = 0; i < mesh->size(); i++) {
		renderer->LoadIdentityMatrix();
		renderer->SetModelMatrix(worldMatrix);

		if (material != NULL) {
			material->Bind();
			material->SetMatrixProperty(renderer->GetWVP());
		}
		renderer->BindTexture(textureId, meshInfo->at(i).textureBufferId);
		renderer->BeginDraw(0);																									// Le decimos al renderer que comience a dibujar
		renderer->BeginDraw(1);
		renderer->BindBuffer(meshInfo->at(i).bufferId, 0);																		// Unimos el buffer con el buffer binding point
		renderer->BindTextureBuffer(meshInfo->at(i).textureBufferId, 1);
		renderer->DrawElementBuffer(meshInfo->at(i).idxCount, meshInfo->at(i).indexBufferId);									// El renderer dibuja el triangulo
		renderer->EndDraw(0);																									// Deja de dibujar
		renderer->EndDraw(1);
	}
}