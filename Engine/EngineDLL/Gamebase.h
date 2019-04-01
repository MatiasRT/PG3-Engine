#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "TypeDef.h"
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
class ENGINEDLL_API Gamebase {
	Window* window;
	double currentFrame;
	double lastFrame;
public:
	Gamebase() { };
	~Gamebase() { };
	bool Start();
	bool Stop();
	void Loop();
	void Time();
protected:
	Renderer * renderer;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
	double time;
};