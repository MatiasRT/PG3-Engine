#include "Gamebase.h"

bool Gamebase::Start() {
	cout << "Gamebase::Start()" << endl;

	window = new Window();
	if (!window->Start(800,600, " "))
		return false;

	renderer = new Renderer();
	if (!renderer->Start(window))
		return false;
	renderer->ClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	renderer->SetPProjectionMatrix(10.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	//renderer->ChangeProjectionMatrix(perspective);				// Si quiero cambiar
	lastFrame = 0;

	return OnStart();
}

void Gamebase::Loop() {
	bool loop = true;
	while (loop && !window->ShouldClose()) {
		Time();
		loop = OnUpdate();

		renderer->ClearScreen();
		OnDraw();
		renderer->SwapBuffers();


		window->PollEvents();
	}
}

bool Gamebase::Stop() {
	cout << "Gamebase::Stop()" << endl;
	OnStop();
	renderer->Stop();
	window->Stop();

	delete renderer;
	delete window;
	return true;
}

void Gamebase::Time() {
	currentFrame = glfwGetTime();					// Aca nos guardamos el tiempo (la hora)
	time = currentFrame - lastFrame;				// Restamos la hora que es en este momento con la hora que era en el frame anterior
	lastFrame = currentFrame;						// Igualamos el ultimo frame al frame actual
}