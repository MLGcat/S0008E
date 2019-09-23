//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#define WIDTH 1000
#define HEIGHT 1000

#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <thread>
#include "scene.h"
#include "skeleton.h"

byte wasd[4] = {0,0,0,0};
float cameraSpeed = 0.1;
float sensitivity = 0.01;
static camera* activeCamera;
bool first = true;
bool mouseDown = false;
float64 lastPosition[2] = {0,0};
float cameraHorizontal, cameraVertical;
bool space;

int mouseWheel;
float scrollSpeed = 1;

struct POINT
{
	float x;
	float y;
};


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

	window->SetMouseScrollFunction([this](int32 a, int32 b)
	{
		mouseWheel = b;
		std::cout << mouseWheel << std::endl;
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
	shaderResource shader;
	shader.loadV("/home/ludfra-7/git/gitlab/Grafikprogrammering/Path tracer/Shaders/VertexShader.txt");
	shader.loadF("/home/ludfra-7/git/gitlab/Grafikprogrammering/Path tracer/Shaders/UnlitFragmentShader.txt");
	shader.compile();
	shader.use();

	meshResource boneMesh;
	boneMesh.load("/home/ludfra-7/git/gitlab/Grafikprogrammering/Skeleton/resources/sphere.obj");

	textureResource boneTex;
	boneTex.loadTexture("/home/ludfra-7/git/gitlab/Grafikprogrammering/Skeleton/resources/mesa.bmp");

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

	Skeleton rig;
	rig.boneMesh = &boneMesh;
	rig.boneShader = &shader;
	rig.boneTexture = &boneTex;
	rig.Load("/home/ludfra-7/git/gitlab/Grafikprogrammering/Skeleton/resources/Unit_Footman.constants");

	mainScene.addObject((Skeleton*)&rig);
	
	int i = 0;
	while (this->window->IsOpen())
	{
		if(wasd[0] != 0)
		{
			activeCamera->move(activeCamera->forward()*(-cameraSpeed));
		}

		if(wasd[1] != 0)
		{
			activeCamera->move(activeCamera->right()*(-cameraSpeed));
		}

		if(wasd[2] != 0)
		{
			activeCamera->move(activeCamera->forward()*cameraSpeed);
		}

		if(wasd[3] != 0)
		{
			activeCamera->move(activeCamera->right()*cameraSpeed);
		}

		if(mouseWheel == 1)
		{
			activeCamera->zoom(-scrollSpeed);
			mouseWheel = 0;

		}
		else if(mouseWheel == -1)
		{
			activeCamera->zoom(scrollSpeed);
			mouseWheel = 0;
		}
		mainScene.draw(*activeCamera);
		this->window->Update();
		this->window->SwapBuffers();
	}
}


}