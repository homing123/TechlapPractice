#pragma once

#include "D3DUtil.h"
#include "MeshData.h"

struct FMesh
{
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	UINT VertexCount = 0;
	UINT IndexCount = 0;
	UINT VertexStirde = 0;
	UINT Offset = 0;

	FMesh() = default;
	FMesh(const FMeshData& meshData);
	void SetMeshData(const FMeshData& meshData);
};