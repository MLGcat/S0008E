//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>

#include "mesh.h"
#include "camera.h"
#include "textureResource.h"
#include "shaderResource.h"
#include "graphicsNode.h"
#include "lightNode.h"

byte wasd[4] = {0,0,0,0};
float cameraSpeed = 0.1;
float sensitivity = 0.01;
static camera* activeCamera;
bool first = true;
bool mouseDown = false;
float64 lastPosition[2] = {0,0};
float cameraHorizontal, cameraVertical;

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

	//SHADER
	shaderResource shader;
	shader.loadV("/home/ludfra-7/git/gitlab/lab-env/Shaders/VertexShader.txt");
	shader.loadF("/home/ludfra-7/git/gitlab/lab-env/Shaders/LitFragmentShader.txt");
	shader.compile();
	shader.use();

	//MESH
	meshResource mesh;
	mesh.load("/home/ludfra-7/git/gitlab/lab-env/Models/hmm.obj");

	//LIGHTS
	light* lightArray[2];
	light l(-5, 0, 0, 1, 1, 1, 0.1);	
	lightArray[0] = &l;
	light l2(5, 0, 0, 1, 1, 1, 0.1);
	lightArray[1] = &l2;


	//TEXTURE
	textureResource texture;
	texture.loadTexture("/home/ludfra-7/git/gitlab/lab-env/Models/hmm.bmp");
	
	//GRAPHIC NODES
	graphicsNode graphic;
	graphic.setMesh(mesh);
	graphic.setShader(shader);
	graphic.setTexture(texture);

	graphic.rotation(0, 0, 0);
	graphic.scale(2,2,2);
	graphic.transform(0, 0, 0);
	graphic.specColor(1, 1, 1, 64, 64);

	graphicsNode graphic2;
	graphic2.setMesh(mesh);
	graphic2.setShader(shader);
	graphic2.setTexture(texture);
	graphic2.specColor(1, 1, 1, 32, 64);


	graphic2.rotation(0, 0, 0);
	graphic2.scale(3, 3, 3);
	graphic2.transform(-10, 0, 0);

	graphicsNode graphic3;
	graphic3.setMesh(mesh);
	graphic3.setShader(shader);
	graphic3.setTexture(texture);
	graphic3.specColor(1, 1, 1, 32, 64);

	graphic3.rotation(90, 0, 0);
	graphic3.scale(3, 3, 3);
	graphic3.transform(10, 0, 0);

	graphicsNode graphic4;
	graphic4.setMesh(mesh);
	graphic4.setShader(shader);
	graphic4.setTexture(texture);
	graphic4.specColor(1, 0, 0, 16, 64);

	graphic4.rotation(0, 0, 0);
	graphic4.scale(3, 3, 3);
	graphic4.transform(0, 0, 10);


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

	float i = 0;


	while (this->window->IsOpen())
	{
		i += 0.01;
		if(wasd[0] != 0)
		{
			activeCamera->move(0, 0, -cameraSpeed);
		}

		if(wasd[1] != 0)
		{
			activeCamera->move(-cameraSpeed, 0, 0);
		}

		if(wasd[2] != 0)
		{
			activeCamera->move(0, 0, cameraSpeed);
		}

		if(wasd[3] != 0)
		{
			activeCamera->move(cameraSpeed, 0, 0);
		}


		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		float dist = 10;

		//Animates objects
		graphic.rotation(100*i, 0, 0);

		//graphic2.transform((5+dist)*sin(i),(5+dist)*cos(i), 0);
		//graphic3.transform((-5-dist)*sin(i), (-5-dist)*cos(i), 0);
		l.setPos((5+dist)*sin(i),(5+dist)*cos(i), 0);
		l2.setPos((-5-dist)*sin(i), (-5-dist)*cos(i), 0);

		//#######################################################################################################

		//Draws objects
		graphic.draw(cam, lightArray,  2);
		graphic2.draw(cam, lightArray, 2);
		graphic3.draw(cam, lightArray, 2);
		graphic4.draw(cam, lightArray, 2);

		this->window->Update();
		this->window->SwapBuffers();
	}
}


}