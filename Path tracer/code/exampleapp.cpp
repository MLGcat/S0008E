//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#define WIDTH 1920
#define HEIGHT 1080

#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <thread>

#include "scene.h"
#include "pathtracer.h"

byte wasd[4] = {0,0,0,0};
float cameraSpeed = 0.1;
float sensitivity = 0.01;
static camera* activeCamera;
bool first = true;
bool mouseDown = false;
float64 lastPosition[2] = {0,0};
float cameraHorizontal, cameraVertical;
PathTracer* pathTracer;
bool space;

struct POINT
{
	float x;
	float y;
};

void StartRender()
{
	int w,h;
	pathTracer->Render(1000000000000000000000, w, h);
}



using namespace Display;
namespace Example
{
ExampleApp::ExampleApp()
{
}
ExampleApp::~ExampleApp()
{
}
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(WIDTH, HEIGHT);
	window->SetKeyPressFunction([this](int32 symbol, int32 keycode, int32 state, int32 something)
	{
		switch(symbol)
		{
			case GLFW_KEY_W:
			wasd[0] = state;
			break;

			case GLFW_KEY_A:
			wasd[1] = state;
			break;

			case GLFW_KEY_S:
			wasd[2] = state;
			break;

			case GLFW_KEY_D:
			wasd[3] = state;
			break;

			case GLFW_KEY_SPACE:
			space = true;
			break;

			case GLFW_KEY_LEFT_SHIFT:
			break;
		}
	});

	window->SetMouseMoveFunction([this](float64 x, float64 y)
	{
		if(!mouseDown) return;
		if(first)
		{
			lastPosition[0] = x;
			lastPosition[1] = y;
			first = false;
		}
		cameraHorizontal += sensitivity * (lastPosition[0] - x);
		cameraVertical += sensitivity * (lastPosition[1] - y);
		lastPosition[0] = x;
		lastPosition[1] = y;
		activeCamera->rotAround(cameraHorizontal, cameraVertical);
	});

	window->SetMousePressFunction([this](int32 key, int32 state, int32 c)
	{
		if(key == 0)
		{
			mouseDown = state == 1;
			if(!mouseDown) first = true;
		}
	});

	if (this->window->Open())
	{

		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		return true;
	}
	return false;
}


void
ExampleApp::Run()
{
	scene mainScene;

	//GUI SHADER
	shaderResource UIShader;
	UIShader.loadV("/home/ludfra-7/git/gitlab/Grafikprogrammering/Path tracer/Shaders/GUIVertexShader.txt");
	UIShader.loadF("/home/ludfra-7/git/gitlab/Grafikprogrammering/Path tracer/Shaders/UnlitFragmentShader.txt");
	UIShader.compile();
	UIShader.use();

	//CAMERA
	camera cam(1, 100, 50, 1);
	cam.setPos(0, 0, 20);
	cam.lookAt(0, 0, 1);
	cam.setAmbient(0.01, 0.01, 0.01);

	activeCamera = &cam;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float camRotH = 0;
	float camRotV = 0;

	POINT lastPos;
	lastPos.x = 0;
	lastPos.y = 0;
	float sensitivity = 0.01;
	bool first = true;


	//PATH TRACER
	meshResource plane;
	plane.load("/home/ludfra-7/git/gitlab/lab-env/Models/plane.obj");

	pathTracer = new PathTracer(WIDTH,HEIGHT);
	textureResource renderOutput;
	renderOutput.width = WIDTH;
	renderOutput.height = HEIGHT;
	renderOutput.img = pathTracer->image;
	graphicsNode renderResult;
	renderResult.setMesh(plane);
	renderResult.setShader(UIShader);
	renderResult.setTexture(renderOutput);
	renderResult.specColor(1, 0, 0, 16, 64);

	renderResult.rotation(0, 0, 0);
	renderResult.scale(3, 3, 3);
	renderResult.transform(0, 30, 10);

	mainScene.addObject(renderResult);
	std::thread renderThread(StartRender);
	renderThread.detach();
	int i = 0;
	while (this->window->IsOpen())
	{
		if(space)
		{
			space = !space;
			FILE * output;
			output = fopen("/home/ludfra-7/Pictures/REEEE.jpg", "wb");
			if(output!= NULL)
			{
				fwrite(pathTracer->image,sizeof(unsigned char*),WIDTH*HEIGHT*3, output);
				fclose(output);
			}
		}
		mainScene.draw(*activeCamera);
		this->window->Update();
		this->window->SwapBuffers();
	}
}


}