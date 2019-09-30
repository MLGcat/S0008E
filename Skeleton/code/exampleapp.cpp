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
#include "Nax3Loader.h"

static camera* activeCamera;
float64 lastMousePosition[2] = {0,0};
float cameraHorizontal, cameraVertical;

bool firstClick = true;
bool wasd[4] = {0,0,0,0};
bool space, shift;
int mouseWheel;
bool mouseDown;

float rotateSpeed = 0.01;
float scrollSpeed = 1;
float shiftSpeed = 0.01;
float translateSpeed = 0.1;

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
			shift = state;
			break;
		}
	});

	window->SetMouseMoveFunction([this](float64 x, float64 y)
	{
		if(!mouseDown) return;
		if(firstClick)
		{
			lastMousePosition[0] = x;
			lastMousePosition[1] = y;
			firstClick = false;
		}
		if(!shift)
		{
			cameraHorizontal += rotateSpeed * (lastMousePosition[0] - x);
			cameraVertical += rotateSpeed * (lastMousePosition[1] - y);
			activeCamera->rotAround(cameraHorizontal, cameraVertical);
		}
		else
		{
			vec4 translation = activeCamera->up()*(lastMousePosition[1] - y) + activeCamera->right() * (lastMousePosition[0] - x);
			translation *= shiftSpeed;
			activeCamera->move(translation);
		}
		lastMousePosition[0] = x;
		lastMousePosition[1] = y;
		
	});

	window->SetMousePressFunction([this](int32 key, int32 state, int32 c)
	{
		if(key == 0)
		{
			mouseDown = state == 1;
			if(!mouseDown) firstClick = true;
		}
	});

	window->SetMouseScrollFunction([this](int32 a, int32 b)
	{
		mouseWheel = b;
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
	Animation animation = Animation::FromNax3("/home/ludfra-7/Downloads/footman/footman/Unit_Footman.nax3");

	scene mainScene;
	
	//GUI SHADER
	shaderResource shader;
	shader.loadV("./build/Shaders/VertexShader.isf");
	shader.loadF("./build/Shaders/UnlitFragmentShader.isf");
	shader.compile();
	shader.use();

	meshResource boneMesh;
	boneMesh.load("./build/Models/sphere.obj");

	textureResource boneTex;
	boneTex.loadTexture("./build/Textures/mesa.bmp");

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

	Skeleton rig;
	rig.boneMesh = &boneMesh;
	rig.boneShader = &shader;
	rig.boneTexture = &boneTex;
	rig.Load("/home/ludfra-7/git/gitlab/Grafikprogrammering/Skeleton/resources/Unit_Footman.constants");

	mainScene.addObject((Skeleton*)&rig);
	
	float i = 0;
	while (this->window->IsOpen())
	{
		i+=1;
		if(wasd[0] != 0)
		{
			activeCamera->move(activeCamera->forward()*(-translateSpeed));
		}

		if(wasd[1] != 0)
		{
			activeCamera->move(activeCamera->right()*(-translateSpeed));
		}

		if(wasd[2] != 0)
		{
			activeCamera->move(activeCamera->forward()*translateSpeed);
		}

		if(wasd[3] != 0)
		{
			activeCamera->move(activeCamera->right()*translateSpeed);
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