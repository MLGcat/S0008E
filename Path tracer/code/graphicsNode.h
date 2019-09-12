#pragma once
#include <memory>
#include "mesh.h"
#include "textureResource.h"
#include "shaderResource.h"
#include "camera.h"
#include "lightNode.h"
class graphicsNode {
public:
	graphicsNode();
	~graphicsNode();
	void setMesh(meshResource & mesh);
	void setShader(shaderResource & shader);
	void setTexture(textureResource & shader);

	void transform(float x, float y, float z);
	void rotation(float x, float y, float z);
	void scale(float x, float y, float z);
	void refreshModel();

	void specColor(float r, float g, float b, float C, float K);

	mat4 model;

	std::shared_ptr<meshResource> getMesh();
	std::shared_ptr<textureResource> getTexture();
	std::shared_ptr<shaderResource> getShader();


	void draw(camera & c, light* lights, unsigned int size);
private:
	std::shared_ptr<meshResource> mesh;
	std::shared_ptr<textureResource> texture;
	std::shared_ptr<shaderResource> shader;
	
	float specData[5];

	mat4 trans, rot, size;

};