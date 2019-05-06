#include "Game.h"

bool Game::OnStart() {
	i = 0;
	translation = 0;
	rotation = 0;
	speed = 0;

	camera = new Camera(renderer);
	Input* input = Input::Instance();
	input->SetWindow(GetWindow());

	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int textureID = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	mat3 = new Material();
	unsigned int tileID = mat3->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	tile = new Tilemap("level.csv", 800, 600, mat3, renderer);

	CollisionManager* instance = CollisionManager::Instance();

	sp1 = new Sprite(renderer, 8, 8);
	sp1->SetMaterial(mat2);
	sp1->LoadBMP("asteroid.bmp");
	sp1->SetPos(15.0f, 4.0f, 0.0f);
	sp1->SetBoundingBox(2.0f, 2.0f, 60.0f, false, false);
	instance->FillingBoxList(Player_layer, sp1);
	sp1->SetAnimation(0, 63, 0.1f);

	sp2 = new Sprite(renderer, 6, 8);
	sp2->SetMaterial(mat2);
	sp2->LoadBMP("character.bmp");
	sp2->SetPos(2.0f, 4.0f, 0.0f);
	sp2->SetBoundingBox(2.0f, 2.0f, 10.0f, false, false);
	instance->FillingBoxList(Enemy_layer, sp2);
	sp2->SetAnimation(0, 47, 0.1f);

	sp3 = new Sprite(renderer, 6, 8);
	sp3->SetMaterial(mat2);
	sp3->LoadBMP("character.bmp");
	sp3->SetPos(8.0f, 0.0f, 0.0f);
	sp3->SetBoundingBox(2.0f, 2.0f, 10.0f, false, true);										// Es trigger
	instance->FillingBoxList(Enemy_layer, sp3);
	sp3->SetAnimation(18, 23, 0.1f);

	sp4 = new Sprite(renderer, 6, 8);
	sp4->SetMaterial(mat2);
	sp4->LoadBMP("character.bmp");
	sp4->SetPos(6.0f, 0.0f, 0.0f);
	sp4->SetBoundingBox(2.0f, 2.0f, 10.0f, false, false);
	instance->FillingBoxList(Enemy_layer, sp4);
	sp4->SetAnimation(0, 5, 0.1f);

	sp5 = new Sprite(renderer, 6, 8);
	sp5->SetMaterial(mat2);
	sp5->LoadBMP("character.bmp");
	sp5->SetPos(-2.0f, -3.0f, 0.0f);
	sp5->SetBoundingBox(2.0f, 2.0f, 10.0f, false, false);
	instance->FillingBoxList(Enemy_layer, sp5);
	sp5->SetAnimation(6, 11, 0.1f);

	sp6 = new Sprite(renderer, 6, 8);
	sp6->SetMaterial(mat2);
	sp6->LoadBMP("character.bmp");
	sp6->SetPos(0.0f, 0.0f, 0.0f);
	sp6->SetBoundingBox(2.0f, 2.0f, 10.0f, false, false);
	instance->FillingBoxList(Enemy_layer, sp6);
	sp6->SetAnimation(0, 47, 0.1f);

	sp7 = new Sprite(renderer, 8, 8);
	sp7->SetMaterial(mat2);
	sp7->LoadBMP("asteroid.bmp");
	sp7->SetPos(-1.0f, 4.0f, 0.0f);
	sp7->SetBoundingBox(2.0f, 2.0f, 10.0f, true, false);										// Es estatico
	instance->FillingBoxList(Bullet_layer, sp7);
	sp7->SetAnimation(0, 63, 0.1f);


	mesh = new Mesh(renderer);
	mesh->SetMaterial(mat1);
	mesh->SetPos(4, 0, 2);

	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	Input* input = Input::Instance();
	CollisionManager::Instance()->BoxCollisionDetector();
	input->PollEvents();
	speed = 1.0f;

	/* TILES */
	tile->UpdateTilemap();
	
	/* CAMARA */
	//renderer->TranslateCamera(glm::vec3(speed * time, 0, 0));

	/* MOVIMIENTO CAMARA */
	if (input->GetInput(GLFW_KEY_W))
		camera->Walk(0, 0.1f);
	if (input->GetInput(GLFW_KEY_S))
		camera->Walk(0, -0.1f);
	if (input->GetInput(GLFW_KEY_A))
		camera->Walk(0.4f, 0);
	if (input->GetInput(GLFW_KEY_D))
		camera->Walk(-0.4f, 0);
	//camera->Walk(0, -0.1f * time);								

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

	//camera->Yaw(0.2f * time);																	
	//camera->Pitch(0.2f * time);																	
	//camera->Roll(0.2f * time);																	
		
	/* ANIMACIONES*/
	sp1->UpdateAnim(time);
	sp2->UpdateAnim(time);
	sp3->UpdateAnim(time);
	sp4->UpdateAnim(time);
	sp5->UpdateAnim(time);
	sp6->UpdateAnim(time);
	sp7->UpdateAnim(time);

	/* MOVIMIENTO */
	/* Movimiento vertical */
	//sp1->TranslationBox(0.0f, -speed * time, 0.0f);											// Movemos con translation asi no pisamos la posicion original
	//sp2->TranslationBox(0.0f, -speed * time, 0.0f);

	/* Movimineto horizontal */
	sp1->TranslationBox(-speed * time * 2, 0.0f, 0.0f);											// Movemos con translation asi no pisamos la posicion original
	sp2->TranslationBox(speed * time, 0.0f, 0.0f);

	/* COLISION CON TILEMAP */
	/* UP */
	if (!tile->CollisionMath(sp3->GetBoundingBox(), Up))
		sp3->TranslationBox(0.0f, speed * time, 0.0f);

	/* DOWN */
	if (!tile->CollisionMath(sp4->GetBoundingBox(), Down))
		sp4->TranslationBox(0.0f, -speed * time, 0.0f);
	
	/* LEFT */
	if (!tile->CollisionMath(sp5->GetBoundingBox(), Left))
		sp5->TranslationBox(-speed * time * 3, 0.0f, 0.0f);

	/* RIGHT */
	if (!tile->CollisionMath(sp6->GetBoundingBox(), Right))
		sp6->TranslationBox(speed * time, 0.0f, 0.0f);

	return true;
}

void Game::OnDraw() {
	//tile->DrawTilemap();

	/*sp1->Draw();
	sp2->Draw();
	sp3->Draw();
	sp4->Draw();
	sp5->Draw();
	sp6->Draw();
	sp7->Draw();*/
	mesh->Draw();
}

bool Game::OnStop() {
	delete sp1;
	delete sp2;
	delete sp3;
	delete sp4;
	delete sp5;
	delete sp6;
	delete sp7;
	delete mat1;
	delete mat2;
	delete tile;
	delete mesh;
	delete camera;
	cout << "Game::OnStop()" << endl;
	return false;
}