#include "MeshData.h"
//Position,
//UV,
//UV2,
//Color,
//Tangent,
map<EVertexElementType, FVertexElementInfo> FMeshData::VertexElementInfoMap =
{
	{Position, FVertexElementInfo(12, "POSITION", DXGI_FORMAT_R32G32B32_FLOAT)},
	{UV, FVertexElementInfo(8, "TEXCOORD", DXGI_FORMAT_R32G32_FLOAT)},
	{EVertexElementType::Color, FVertexElementInfo(12, "Color", DXGI_FORMAT_R32G32B32_FLOAT)},
	{EVertexElementType::Tangent, FVertexElementInfo(12, "TANGENT", DXGI_FORMAT_R32G32B32_FLOAT)},
};

FMeshData FMeshData::QuadMeshData = FMeshData
(
	vector<EVertexElementType>{Position, UV},
	vector<float>
{
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
},
vector<int32_t>{0, 1, 2, 0, 2, 3}
);

FMeshData FMeshData::CubeMeshData = FMeshData
(
	vector<EVertexElementType>{Position, UV},
	vector<float>
{
	// Front face (Z = -0.5)
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

		// Back face (Z = 0.5)
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,

		// Left face (X = 0.5)
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,

		// Right face (X = -0.5)
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

		// Top face (Y = 0.5)
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,

		// Bottom face (Y = -0.5)
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
},
vector<int32_t>
{
	// Front face
	0, 1, 2, 0, 2, 3,
		// Back face  
		4, 5, 6, 4, 6, 7,
		// Left face
		8, 9, 10, 8, 10, 11,
		// Right face
		12, 13, 14, 12, 14, 15,
		// Top face
		16, 17, 18, 16, 18, 19,
		// Bottom face
		20, 21, 22, 20, 22, 23
}
);