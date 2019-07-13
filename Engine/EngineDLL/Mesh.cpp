#include "Mesh.h"

Mesh::Mesh(Renderer * renderer, const std::string& name, const char * name2) : Component(renderer){

	type = ComponentsType::MeshRenderType;

	meshInfo = new std::vector<MeshInfo>();
	mesh = new std::vector<MeshEntry>();

	Importer::LoadMesh(name, mesh);										// Cargo el mesh

	meshInfo->resize(mesh->size());										

	for (int i = 0; i < mesh->size(); i++) {							// Cargo los atributos de meshInfo con lo recibido del importer
		meshInfo->at(i).shouldDispose = false;
		meshInfo->at(i).shouldDisposeTexture = false;
		meshInfo->at(i).shouldDisposeIndices = false;

		meshInfo->at(i).bufferId = -1;
		meshInfo->at(i).textureBufferId = -1;
		meshInfo->at(i).indexBufferId = -1;

		meshInfo->at(i).vtxCount = mesh->at(i).vertices->size();		// Cargo la cantidad de vertices en el atributo de meshInfo
		meshInfo->at(i).vtxTextureCount = mesh->at(i).texture->size();	// Cargo la cantidad vertices de texturas en el atributo de meshInfo
		meshInfo->at(i).idxCount = mesh->at(i).indices->size();			// Cargo la cantidad de indices en el atributo de meshInfo

		meshInfo->at(i).vertex = new float[meshInfo->at(i).vtxCount];	// Genero el vector de vertices segun lo guardado

		for (int j = 0; j < meshInfo->at(i).vtxCount; j++) 
			meshInfo->at(i).vertex[j] = mesh->at(i).vertices->at(j);	// Lo cargo
		
		SetVertices(i);


		meshInfo->at(i).textureVertex = new float[meshInfo->at(i).vtxTextureCount]; // Genero el vector de vertices de texturas segun lo guardado

		for (int k = 0; k < meshInfo->at(i).vtxTextureCount; k++)
			meshInfo->at(i).textureVertex[k] = mesh->at(i).texture->at(k);	// Lo cargo

		SetTextureVertices(i);



		meshInfo->at(i).indices = new unsigned int[meshInfo->at(i).idxCount]; // Genero el vector de indices segun lo guardado

		for (int l = 0; l < meshInfo->at(i).idxCount; l++)
			meshInfo->at(i).indices[l] = mesh->at(i).indices->at(l);		// lo cargo


		SetIndexVertices(i);

		meshInfo->at(i).material = new Material();
		meshInfo->at(i).programId = meshInfo->at(i).material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
		LoadMaterial(name2, meshInfo->at(i).textureId, meshInfo->at(i).material);
	}
}

Mesh::~Mesh() {
	for (int i = 0; i < mesh->size(); i++) {
		delete[] meshInfo->at(i).vertex;
		delete[] meshInfo->at(i).textureVertex;
		delete[] meshInfo->at(i).indices;
		delete meshInfo->at(i).material;
	}
	delete mesh;
	delete meshInfo;
}

/*void Mesh::LoadMaterial(const char * name) {

	header = Importer::LoadBMP(name);
	textureId = renderer->UploadData(header.width, header.height, header.data);
	material->BindTexture();
	
}*/

void Mesh::LoadMaterial(const char * name, unsigned int & textureId, Material * material) {
	header = Importer::LoadBMP(name);
	textureId = renderer->UploadData(header.width, header.height, header.data);
	material->BindTexture();
}

void Mesh::SetVertices(int index) {
	//Dispose();

	meshInfo->at(index).shouldDispose = true;
	meshInfo->at(index).bufferId = renderer->GenBuffer(meshInfo->at(index).vertex,
		sizeof(float)* meshInfo->at(index).vtxCount);
}

void Mesh::SetTextureVertices(int index) {
	DisposeTexture();
	meshInfo->at(index).shouldDisposeTexture = true;
	meshInfo->at(index).textureBufferId = renderer->GenBuffer(meshInfo->at(index).textureVertex,
		sizeof(float)* meshInfo->at(index).vtxTextureCount);
}

void Mesh::SetIndexVertices(int index) {
	DisposeIndex();

	meshInfo->at(index).shouldDisposeIndices = true;
	meshInfo->at(index).indexBufferId = renderer->GenElementBuffer(meshInfo->at(index).indices,
		sizeof(int) * meshInfo->at(index).idxCount);
}

void Mesh::DisposeIndex() {

}

void Mesh::DisposeTexture() {

}

/*void Mesh::SetVertices(MeshInfo& mesh) {

	DisposeVertices(mesh.shouldDispose, mesh.bufferId);

	mesh.shouldDispose = true;

	mesh.bufferId = renderer->GenBuffer(mesh.vertex, sizeof(float) * mesh.vtxCount);		// Genero el buffer con lo guardado en meshInfo, que fue sacado de lo recibido en importer
}

void Mesh::SetTextureVertices(MeshInfo & mesh) {

	DisposeTextures(mesh.shouldDisposeTexture, mesh.textureBufferId);

	mesh.shouldDisposeTexture = true;

	mesh.textureBufferId = renderer->GenBuffer(mesh.textureVertex, sizeof(float) * mesh.vtxTextureCount); // Genero el buffer de textura con lo guardado en meshInfo, que fue sacado de lo recibido en importer
}

void Mesh::SetIndexVertices(MeshInfo & mesh) {
	DisposeIndex(mesh.shouldDisposeIndices, mesh.indexBufferId);

	mesh.shouldDisposeIndices = true;
	
	mesh.indexBufferId = renderer->GenElementBuffer(mesh.indices, sizeof(int) * mesh.idxCount); // Genero el buffer de indices con lo guardado en meshInfo, que fue sacado de lo recibido en importer
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
}*/

void Mesh::Draw() {

	for (int i = 0; i < mesh->size(); i++) {
		renderer->LoadIdentityMatrix();
		renderer->SetModelMatrix(worldMatrix);

		if (material != NULL) {
			material->Bind();
			material->SetMatrixProperty(renderer->GetWVP());
		}
		renderer->BindTexture(meshInfo->at(i).textureId, meshInfo->at(i).textureBufferId);
		renderer->BeginDraw(0);																									// Le decimos al renderer que comience a dibujar
		renderer->BeginDraw(1);
		renderer->BindBuffer(meshInfo->at(i).bufferId, 0);																		// Unimos el buffer con el buffer binding point
		renderer->BindTextureBuffer(meshInfo->at(i).textureBufferId, 1);
		renderer->DrawElementBuffer(meshInfo->at(i).idxCount, meshInfo->at(i).indexBufferId);									// El renderer dibuja el triangulo
		renderer->EndDraw(0);																									// Deja de dibujar
		renderer->EndDraw(1);
	}
}

void Mesh::SetMaterial(Material* material) {
	this->material = material;
}