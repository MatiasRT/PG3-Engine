#include "Mesh.h"

Mesh::Mesh(Renderer * renderer, const char * txtFile, Camera * cam) : Component(renderer) {
	type = ComponentsType::MeshRenderType;
	camera = cam;
	collider = new Collider(renderer);

	textureFile = txtFile;
	meshInfo = new MeshInfo;
	meshData = new MeshData();

	meshInfo->shouldDisposeVertices = false;
	meshInfo->shouldDisposeIndices = false;
	meshInfo->shouldDisposeTexture = false;

	meshInfo->bufferId = -1;
	meshInfo->textureBufferId = -1;
	meshInfo->indexBufferId = -1;
}

Mesh::~Mesh() {
	delete[] meshInfo->vertex;
	delete[] meshInfo->textureVertex;
	delete[] meshInfo->indices;
	delete meshInfo->material;
	delete meshInfo;
	delete meshData;
	delete collider;
}

void Mesh::SetMeshData(MeshData * meshD) {
	meshData = meshD;
	meshInfo->vtxCount = meshData->vertices->size();
	meshInfo->idxCount = meshData->indices->size();
	meshInfo->textureCount = meshData->textures->size();

	meshInfo->vertex = new float[meshInfo->vtxCount];
	for (int i = 0; i < meshInfo->vtxCount; i++)
		meshInfo->vertex[i] = meshData->vertices->at(i);

	DisposeVertices();

	meshInfo->shouldDisposeVertices = true;
	meshInfo->bufferId = renderer->GenBuffer(meshInfo->vertex, sizeof(float)* meshInfo->vtxCount);


	meshInfo->textureVertex = new float[meshInfo->textureCount];
	for (int k = 0; k < meshInfo->textureCount; k++) 
		meshInfo->textureVertex[k] = meshData->textures->at(k);

	DisposeTexture();

	meshInfo->shouldDisposeTexture = true;
	meshInfo->textureBufferId = renderer->GenBuffer(meshInfo->textureVertex, sizeof(float)* meshInfo->textureCount);

	meshInfo->indices = new unsigned int[meshInfo->idxCount];
	for (int j = 0; j < meshInfo->idxCount; j++) 
		meshInfo->indices[j] = meshData->indices->at(j);
	
	DisposeIndices();

	meshInfo->shouldDisposeIndices = true;
	meshInfo->indexBufferId = renderer->GenElementBuffer(meshInfo->indices, sizeof(int)* meshInfo->idxCount);

	meshInfo->material = new Material();
	meshInfo->programId = meshInfo->material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	header = Importer::LoadBMP(textureFile);
	meshInfo->textureId = renderer->UploadData(header.width, header.height, header.data);
	meshInfo->material->BindTexture();
}

void Mesh::Draw() {
	if (camera->BoxInFrustum(collider) == CameraStates::In) {
		if (meshInfo->material != NULL) {
			meshInfo->material->Bind();
			meshInfo->material->SetMatrixProperty(renderer->GetWVP());
		}
		renderer->BindTexture(meshInfo->textureId, meshInfo->textureBufferId);
		renderer->BeginDraw(0);																									// Le decimos al renderer que comience a dibujar
		renderer->BeginDraw(1);
		renderer->BindBuffer(meshInfo->bufferId, 0);																			// Unimos el buffer con el buffer binding point
		renderer->BindBuffer(1, meshInfo->textureBufferId, 2);
		renderer->DrawElementBuffer(meshInfo->idxCount, meshInfo->indexBufferId);												// El renderer dibuja el triangulo
		renderer->EndDraw(0);																									// Deja de dibujar
		renderer->EndDraw(1);
	}
}

void Mesh::DisposeVertices() {
	if (meshInfo->shouldDisposeVertices) {
		renderer->DestroyBuffer(meshInfo->bufferId);
		meshInfo->shouldDisposeVertices = false;
	}
}

void Mesh::DisposeIndices() {
	if (meshInfo->shouldDisposeIndices) {
		renderer->DestroyBuffer(meshInfo->indexBufferId);
		meshInfo->shouldDisposeIndices = false;
	}
}

void Mesh::DisposeTexture() {
	if (meshInfo->shouldDisposeTexture) {
		renderer->DestroyBuffer(meshInfo->textureBufferId);
		meshInfo->shouldDisposeTexture = false;
	}
}