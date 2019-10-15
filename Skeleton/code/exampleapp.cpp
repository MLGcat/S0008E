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
#include "Animation.h"
#include "skinnedMesh.h"

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

unsigned int currentAnimation = 6;

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

			case GLFW_KEY_1:
			case GLFW_KEY_2:
			case GLFW_KEY_3:
			case GLFW_KEY_4:
			case GLFW_KEY_5:
			case GLFW_KEY_6:
			case GLFW_KEY_7:
			case GLFW_KEY_8:
			case GLFW_KEY_9:
			currentAnimation = symbol - 49;
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
	

	shaderResource skinShader;
	skinShader.loadV("./build/Shaders/SkinVertexShader.isf");
	skinShader.loadF("./build/Shaders/LitFragmentShader.isf");
	skinShader.compile();
	skinShader.use();


	Animation animation = Animation::FromNax3("/home/ludfra-7/Downloads/footman/footman/Unit_Footman.nax3");
	SkinnedMesh skin;
	skin.LoadNVX2("/home/ludfra-7/Downloads/footman/footman/Unit_Footman.nvx2");
	scene mainScene;

	meshResource boneMesh;
	boneMesh.load("./build/Models/sphere.obj");

	textureResource diffuse(0);
	diffuse.loadTexture("/home/ludfra-7/Downloads/footman/footman/Footman_Diffuse.tga");

	textureResource normal(1);
	normal.loadTexture("/home/ludfra-7/Downloads/footman/footman/Footman_Normal.tga");


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
	rig.boneShader = &skinShader;
	rig.boneTexture = &diffuse;
	rig.animation = &animation;
	rig.showSkeleton = false;

	rig.setMesh(skin);
	rig.setShader(skinShader);
	rig.addTexture(diffuse);
	rig.addTexture(normal);

	light asd(vec4(1,0,0), vec4(1,1,1), 1);


	rig.Load("/home/ludfra-7/git/gitlab/Grafikprogrammering/Skeleton/resources/Unit_Footman.constants");
	unsigned int lastAnimation = 0;

	mainScene.addLight(asd);
	mainScene.addObject((Skeleton*)&rig);
	
	std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds time = start - start;

	while (this->window->IsOpen())
	{
		if(lastAnimation != currentAnimation)
		{
			std::cout << "Playing animation: " << rig.animation->Clips[currentAnimation].name << std::endl;
			lastAnimation = currentAnimation;
		}

		std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		std::chrono::milliseconds delta = now - start;
		time += delta;
		rig.ApplyKey(currentAnimation,(float)(delta.count())/1000);
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