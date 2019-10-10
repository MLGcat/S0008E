#pragma once
//------------------------------------------------------------------------------
/**
    @file naxfileformatstructs.h
    
    nvx2 file format structures.
    
    (C) 2009 Radon Labs GmbH
    (C) 2013-2016 Individual contributors, see AUTHORS file
*/

#pragma pack(push, 1)

#define NEBULA3_NVX2_MAGICNUMBER 'NVX2'

//------------------------------------------------------------------------------
/** 
    NVX2 file format structs.
    NOTE: keep all header-structs 4-byte aligned!
*/

enum N2VertexComponent
{
    N2Coord        = (1<<0),      // 3 floats
    N2Normal       = (1<<1),      // 3 floats
    N2NormalB4N   = (1<<2),      // 4 unsigned bytes, normalized
    N2Uv0          = (1<<3),      // 2 floats
    N2Uv0S2        = (1<<4),      // 2 shorts, 4.12 fixed point
    N2Uv1          = (1<<5),      // 2 floats
    N2Uv1S2        = (1<<6),      // 2 shorts, 4.12 fixed point
    N2Uv2          = (1<<7),      // 2 floats
    N2Uv2S2        = (1<<8),      // 2 shorts, 4.12 fixed point
    N2Uv3          = (1<<9),      // 2 floats
    N2Uv3S2        = (1<<10),     // 2 shorts, 4.12 fixed point
    N2Color        = (1<<11),     // 4 floats
    N2ColorUB4N    = (1<<12),     // 4 unsigned bytes, normalized
    N2Tangent      = (1<<13),     // 3 floats
    N2TangentB4N  = (1<<14),     // 4 unsigned bytes, normalized
    N2Binormal     = (1<<15),     // 3 floats
    N2BinormalB4N = (1<<16),     // 4 unsigned bytes, normalized
    N2Weights      = (1<<17),     // 4 floats
    N2WeightsUB4N  = (1<<18),     // 4 unsigned bytes, normalized
    N2JIndices     = (1<<19),     // 4 floats
    N2JIndicesUB4  = (1<<20),     // 4 unsigned bytes

    N2NumVertexComponents = 21,
    N2AllComponents = ((1<<N2NumVertexComponents) - 1),
};

struct Nvx2Header
{
	unsigned int magic;
	unsigned int numGroups;
	unsigned int numVertices;
	unsigned int vertexWidth;
	unsigned int numIndices;
	unsigned int numEdges;
	unsigned int vertexComponentMask;
};

struct Nvx2Group
{
	unsigned int firstVertex;
	unsigned int numVertices;
	unsigned int firstTriangle;
	unsigned int numTriangles;
	unsigned int firstEdge;
	unsigned int numEdges;
};

#pragma pack(pop)