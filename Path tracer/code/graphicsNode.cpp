#include "graphicsNode.h"

graphicsNode::graphicsNode() {
}

graphicsNode::~graphicsNode(){
}

void graphicsNode::draw(camera & c, light** lights, unsigned int size) {
	shader->use();
	texture->use(shader->program);

	glUniformMatrix4fv(glGetUniformLocation(shader->program, "m"), 1, GL_TRUE, model.get());
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "v"), 1, GL_TRUE, c.view().get());
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "p"), 1, GL_TRUE, c.perspective().get());

	//Lights
	glUniform1ui(glGetUniformLocation(shader->program, "lightArraySize"), size);
	for (int i = 0; i < size; i++) {
		string name = "lightArray[" + std::to_string(i) + "]";
		glUniform1fv(glGetUniformLocation(shader->program, (name + ".pos").c_str()), 4, lights[i]->pos);
		glUniform1uiv(glGetUniformLocation(shader->program, (name + ".col").c_str()), 3, lights[i]->color);
		glUniform1f(glGetUniformLocation(shader->program, (name + ".intensity").c_str()), lights[i]->intensity);
	}

	//Camera
	float* test = &c.pos.get3();
	GLfloat test2[3];
	test2[0] = test[0];
	test2[1] = test[1];
	test2[2] = test[2];
	glUniform1fv(glGetUniformLocation(shader->program, "camPos"), 3, test2);
	glUniform1fv(glGetUniformLocation(shader->program, "ambientLight"), 3, c.ambientLight);

	//Specular data
	glUniform1fv(glGetUniformLocation(shader->program, "specData"), 5, specData);

	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->fCount*3, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void graphicsNode::specColor(float r, float g, float b, float C, float K) {
	specData[0] = r;
	specData[1] = g;
	specData[2] = b;
	specData[3] = C;
	specData[4] = K;
}

//SET
void graphicsNode::setMesh(meshResource & mesh) {
	this->mesh = make_shared<meshResource>(mesh);
}

void graphicsNode::setShader(shaderResource & shader) {
	this->shader = make_shared<shaderResource>(shader);
}

void graphicsNode::setTexture(textureResource & texture) {
	this->texture = make_shared<textureResource>(texture);
}

//TRANSFORM
void graphicsNode::transform(float x, float y, float z) {
	trans = matrix4D::transform(x, y, z);
	refreshModel();
}

void graphicsNode::rotation(float x, float y, float z) {
	rot = matrix4D::rotd3(x, y, z);
	refreshModel();
}

void graphicsNode::scale(float x, float y, float z) {
	size = matrix4D::scale(x, y, z);
	refreshModel();
}

void graphicsNode::refreshModel() {
	model = trans*rot*size;
}

//GET
std::shared_ptr<meshResource> graphicsNode::getMesh() {
	return mesh;
}

std::shared_ptr<textureResource> graphicsNode::getTexture() {
	return texture;
}

std::shared_ptr<shaderResource> graphicsNode::getShader() {
	return shader;
}