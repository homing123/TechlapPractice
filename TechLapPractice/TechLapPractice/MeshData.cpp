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
			-0.5f, -0.5f,  0.0f,	0.0f, 1.0f,
			-0.5f,  0.5f,  0.0f,	0.0f, 0.0f,
			 0.5f,  0.5f,  0.0f,	1.0f, 0.0f,
			 0.5f, -0.5f,  0.0f,	1.0f, 1.0f,
	},
	vector<int32_t>{0, 1, 2, 0, 2, 3}
);

FMeshData FMeshData::CubeMeshData = FMeshData
(
	vector<EVertexElementType>{Position, UV},
	vector<float>
	{
			-0.5f, -0.5f,  0.0f,	0.0f, 1.0f,
			-0.5f,  0.5f,  0.0f,	0.0f, 0.0f,
			 0.5f,  0.5f,  0.0f,	1.0f, 0.0f,
			 0.5f, -0.5f,  0.0f,	1.0f, 1.0f,
	},
	vector<int32_t>{0, 1, 2, 0, 2, 3}
);