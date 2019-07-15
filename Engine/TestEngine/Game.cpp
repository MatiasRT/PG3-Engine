#include "Game.h"

bool Game::OnStart() {
	i = 0;
	translation = 0;
	rotation = 0;
	speed = 0;

	camera = new Camera(renderer);
	Input* input = Input::Instance();
	input->SetWindow(GetWindow());

	/*mat1 = new Material();																	// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int textureID = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	mat3 = new Material();
	unsigned int tileID = mat3->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");*/


	/*Nodos*/
	sceneNode = new GameNode(renderer);
	cameraNode = new GameNode(renderer);
	firstNode = new GameNode(renderer);
	secondNode = new GameNode(renderer);

	/* Jerarquia de Nodos*/
	sceneNode->AddChild(cameraNode);
	sceneNode->AddChild(firstNode);
	firstNode->AddChild(secondNode);



	/*cargo los modelos*/
	cameraNode->AddComponent(camera);
	Importer::LoadMesh("sword.fbx", "sword.bmp", secondNode, renderer, camera);
	//Importer::LoadMesh("car.fbx", "car.bmp", secondNode, renderer, camera);
	//Importer::LoadMesh("weapon3.fbx", "weapon3.bmp", secondNode, renderer, camera);
	
	/*seteo la escala y posicion*/

	secondNode->SetScale(0.1f, 0.1f, 0.1f);
	//secondNode->SetPos(10, 0, 0);

	SetSceneNode(sceneNode);

	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	Input* input = Input::Instance();
	//CollisionManager::Instance()->BoxCollisionDetector();
	input->PollEvents();
	speed = 1.0f;

	/* NODES */
	secondNode->GetNode(1)->Rotate(0, time, 0);
	//secondNode->GetNode(1)->SetRotY(sceneNode->GetNode(1)->GetRot().y + time * speed); //REVISAR

	//secondNode->Rotate(time,0.0f,0.0f);


	/* MOVIMIENTO CAMARA */
	if (input->GetInput(GLFW_KEY_W))
		camera->Walk(0, 0.1f);
	if (input->GetInput(GLFW_KEY_S))
		camera->Walk(0, -0.1f);
	if (input->GetInput(GLFW_KEY_A))
		camera->Walk(0.4f, 0);
	if (input->GetInput(GLFW_KEY_D))
		camera->Walk(-0.4f, 0);								

	/* ROTACION CAMARA */
	if (input->GetInput(GLFW_KEY_UP))
		camera->Pitch(-0.01f);
	if (input->GetInput(GLFW_KEY_DOWN))
		camera->Pitch(0.01f);
	if (input->GetInput(GLFW_KEY_LEFT))
		camera->Yaw(0.01f);
	if (input->GetInput(GLFW_KEY_RIGHT))
		camera->Yaw(-0.01f);
	if (input->GetInput(GLFW_KEY_Q))
		camera->Roll(-0.01f);
	if (input->GetInput(GLFW_KEY_E))
		camera->Roll(0.01f);


	return true;
}

bool Game::OnStop() {
	delete sceneNode;
	delete cameraNode;
	delete firstNode;
	delete secondNode;

	delete camera;
	cout << "Game::OnStop()" << endl;
	return false;
}