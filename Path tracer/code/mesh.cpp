#include "mesh.h"


meshResource::meshResource()
{
}

meshResource::meshResource(GLfloat* verts, int length, GLuint* index, int faces)
{
	//Copies vertex and index arrays
	this->verts = verts;
	this->index = index;

	vCount = length;
	fCount = faces;

}

meshResource::~meshResource()
{
}

void meshResource::bake() {
		glEnable(GL_TEXTURE_2D);

		//Binder vao till buffer
		glGenVertexArrays(1, &vao); 
		glBindVertexArray(vao); 

		//VERTISER
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vCount*9, verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, NULL); //Vertex
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3)); //Normal
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6)); //UV
		glBindBuffer(GL_ARRAY_BUFFER, 0); //Obinder vertisbuffer

		//INDEX
		glGenBuffers(1, &this->ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 3 * fCount, index, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0); //Obinder indexbuffer

		glBindVertexArray(0);
}

void meshResource::load(char* src) {
	FILE * file = fopen(src, "r");
	if (file == NULL) {
		std::cout << "Failed to load file!" << std::endl;
		return;
	}

	std::vector<vector4D> vertVec;
	std::vector<vector4D> normVec;
	std::vector<vector4D> uvVec;
	std::vector<face> faceVec;

	char line[128];
	while (true) {
		if (fscanf(file, "%s", line)==EOF) break;
		if (strcmp(line, "v") == 0) {
			float x,y,z = 0;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			vector4D vert(x, y, z);
			vertVec.push_back(vert);
			//std::cout << "v " << x << ", " << y << ", " << z << " (" << vertsVec.size() << ")" << std::endl;
		}
		else if(strcmp(line, "vt")==0){
			float x, y = 0;
			fscanf(file, "%f %f\n", &x, &y);
			vector4D uv(x, y, 0);
			uvVec.push_back(uv);
			//std::cout << "vt " << x << ", " << y << " (" << uvVec.size() << ")" << std::endl;
		}
		else if (strcmp(line, "vn") == 0) {
			float x, y, z = 0;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			vector4D norm(x, y, z);
			normVec.push_back(norm);
			//std::cout << "vn " << x << ", " << y << ", " << z << " (" << normVec.size() << ")" << std::endl;
		}
		else if (strcmp(line, "f") == 0) {
			face tempFace;
			float test; 
			face tempFace2;
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&tempFace.verts[0].coord, &tempFace.verts[0].uv, &tempFace.verts[0].normal,
				&tempFace.verts[1].coord, &tempFace.verts[1].uv, &tempFace.verts[1].normal,
				&tempFace.verts[2].coord, &tempFace.verts[2].uv, &tempFace.verts[2].normal,
				&tempFace2.verts[0].coord, &tempFace2.verts[0].uv, &tempFace2.verts[0].normal);
			if (tempFace2.verts[0].coord != -1083184041 && tempFace2.verts[0].coord !=1060164023) {
				tempFace2.verts[1] = tempFace.verts[0];
				tempFace2.verts[2] = tempFace.verts[2];
				faceVec.push_back(tempFace2);
				std::cout << "Quad divided!" << std::endl;
			}
			faceVec.push_back(tempFace);
		}
	}

	GLfloat* newVerts = new GLfloat[faceVec.size() * 24];

	for (size_t i = 0; i < faceVec.size(); i++) //For every face
	{
		int fOffset = i * 24;
		for (size_t j = 0; j < 3; j++) //For every pos in face
		{
			int vOffset = j * 8;
			//x,y,z
			newVerts[fOffset + vOffset]		= vertVec[faceVec[i].verts[j].coord - 1][0];
			newVerts[fOffset + vOffset + 1] = vertVec[faceVec[i].verts[j].coord - 1][1];
			newVerts[fOffset + vOffset + 2] = vertVec[faceVec[i].verts[j].coord - 1][2];

			newVerts[fOffset + vOffset + 3] = normVec[faceVec[i].verts[j].normal - 1][0];
			newVerts[fOffset + vOffset + 4] = normVec[faceVec[i].verts[j].normal - 1][1];
			newVerts[fOffset + vOffset + 5] = normVec[faceVec[i].verts[j].normal - 1][2];

			newVerts[fOffset + vOffset + 6] = uvVec[faceVec[i].verts[j].uv - 1][0];
			newVerts[fOffset + vOffset + 7] = uvVec[faceVec[i].verts[j].uv - 1][1];
			//newInd[i] = faceVec[][];
		}
	}

	GLuint* newInd = new GLuint[faceVec.size() * 24];
	for (size_t i = 0; i < faceVec.size()*24; i++)
	{
		newInd[i] = i;
	}

	fCount = faceVec.size();
	vCount = faceVec.size() * 3;
	verts = newVerts;
	index = newInd;

	/*for (size_t i = 0; i < vCount; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << newVerts[i*8 + j] << ",";
		}
		std::cout << std::endl;
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << newVerts[i*8 + j+3] << ",";
		}
		std::cout << std::endl;
		for (size_t j = 0; j < 2; j++)
		{
			std::cout << newVerts[i*8 + j+6] << ",";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}*/
	bake();
}

