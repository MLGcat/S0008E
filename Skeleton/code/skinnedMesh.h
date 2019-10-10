#pragma once
#include "mesh.h"
class SkinnedMesh : public meshResource
{
public:
    
    SkinnedMesh LoadNVX2(const char path[])
    {
        std::ifstream stream(path, std::ifstream::binary);
        if(stream)
        {
            unsigned int bytesRead = 0;

            stream.seekg(0, std::ifstream::end);
            unsigned int length = stream.tellg();
            stream.seekg(0, std::ifstream::beg);

            char* buffer = new char[length];
            stream.read(buffer, length);
            stream.close();

            char* ptr = buffer;

            Nvx2Header* header = (Nvx2Header*)ptr;
            ptr += sizeof(Nvx2Header);
            bytesRead += sizeof(Nvx2Header);

            vCount = header->numVertices;
            
            GLchar* dataPtr = ptr + sizeof(Nvx2Group)*header->numGroups;

            verts = (GLfloat*)new unsigned char[header->numVertices*header->vertexWidth];
            unsigned int vertsOffset = 0;

            for(int group = 0; group < header->numGroups; group++)
            {
                Nvx2Group* currGroup = (Nvx2Group*)ptr;
                ptr += sizeof(Nvx2Group);
                
                fCount = currGroup->numTriangles;

                verts = new GLfloat[currGroup->numVertices * header->vertexWidth];
                memcpy(verts, dataPtr, currGroup->numVertices * header->vertexWidth * sizeof(GLfloat));

                unsigned int bufferCount = 0;
                GLchar* offset = 0;

                glEnable(GL_TEXTURE_2D);
                //Binder vao till buffer
                glGenVertexArrays(1,&vao); 
                glBindVertexArray(vao); 

                //VERTISER
                glGenBuffers(1, &vbo);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*header->numVertices*header->vertexWidth, verts, GL_STATIC_DRAW);
                dataPtr += sizeof(GLfloat)*header->numVertices*header->vertexWidth;
                int test = 0;
                for (unsigned int i = 0; i < 21; i++)
                {
                    if (header->vertexComponentMask & (1<<i))
                    {
		                glEnableVertexAttribArray(bufferCount);
                        switch (1<<i)
                        {
                            case N2Coord:         glVertexAttribPointer(bufferCount, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 3;  offset += sizeof(GLfloat) * 3; break;
                            case N2Normal:        glVertexAttribPointer(bufferCount, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 3;  offset += sizeof(GLfloat) * 3; break;
                            case N2NormalB4N:     glVertexAttribPointer(bufferCount, 4, GL_BYTE, GL_TRUE,  sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);          test += 4; offset += sizeof(GLbyte) * 4;   break;
                            case N2Uv0:           glVertexAttribPointer(bufferCount, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 2;  offset += sizeof(GLfloat) * 2; break;
                            case N2Uv0S2:         glVertexAttribPointer(bufferCount, 2, GL_SHORT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 2;  offset += sizeof(GLshort) * 2; break;
                            case N2Uv1:           glVertexAttribPointer(bufferCount, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 2;  offset += sizeof(GLfloat) * 2; break;
                            case N2Uv1S2:         glVertexAttribPointer(bufferCount, 2, GL_SHORT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 2;  offset += sizeof(GLshort) * 2; break;
                            case N2Color:         glVertexAttribPointer(bufferCount, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 4;  offset += sizeof(GLfloat) * 4; break;
                            case N2ColorUB4N:     glVertexAttribPointer(bufferCount, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);  test += 4; offset += sizeof(GLbyte) * 4;  break;
                            case N2Tangent:       glVertexAttribPointer(bufferCount, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 3;  offset += sizeof(GLfloat) * 3; break;
                            case N2TangentB4N:    glVertexAttribPointer(bufferCount, 4, GL_BYTE, GL_TRUE,  sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);          test += 4; offset += sizeof(GLbyte) * 4;  break;
                            case N2Binormal:      glVertexAttribPointer(bufferCount, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 3;  offset += sizeof(GLfloat) * 3; break;
                            case N2BinormalB4N:   glVertexAttribPointer(bufferCount, 4, GL_BYTE, GL_TRUE,  sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);          test += 4; offset += sizeof(GLbyte) * 4;  break;
                            case N2Weights:       glVertexAttribPointer(bufferCount, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 4;  offset += sizeof(GLfloat) * 4; break;
                            case N2WeightsUB4N:   glVertexAttribPointer(bufferCount, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);  test += 4; offset += sizeof(GLbyte) * 4;  break;
                            case N2JIndices:      glVertexAttribPointer(bufferCount, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset);         test += 4;  offset += sizeof(GLfloat) * 4; break;
                            case N2JIndicesUB4:   glVertexAttribPointer(bufferCount, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GLfloat) * header->vertexWidth, (GLvoid*)offset); test += 4;  offset += sizeof(GLbyte) * 4;  break;
                        }
                        
                        bufferCount++;
                    }
                }

		        glBindBuffer(GL_ARRAY_BUFFER, 0); //Obinder vertisbuffer

                index = new GLuint[header->numIndices * 3];
                memcpy(index, dataPtr, header->numIndices * sizeof(GLuint) * 3);

                
            }

            delete buffer;
            //INDEX
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, fCount * sizeof(GLuint) * 3, index, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0); //Obinder indexbuffer

            glBindVertexArray(0);
        }
    }
};