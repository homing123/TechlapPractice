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
	FMesh(ID3D11Device* device, const FMeshData& meshData)
	{
		D3DUtil::CreateVertexBuffer(device, meshData.GetVertexValues(), meshData.GetVertexByteWidth(), &VertexBuffer);
		D3DUtil::CreateIndexBuffer(device, meshData.GetIndices(), &IndexBuffer);
		VertexCount = meshData.GetVertexCount();
		IndexCount = meshData.GetIndexCount();
		VertexStirde = meshData.GetVertexByteWidth();
	}

	void SetMeshData(ID3D11Device* device, const FMeshData& meshData)
	{
		if (VertexBuffer != nullptr)
		{
			VertexBuffer->Release();
		}
		if (IndexBuffer != nullptr)
		{
			IndexBuffer->Release();
		}
		D3DUtil::CreateVertexBuffer(device, meshData.GetVertexValues(), meshData.GetVertexByteWidth(), &VertexBuffer);
		D3DUtil::CreateIndexBuffer(device, meshData.GetIndices(), &IndexBuffer);
		VertexCount = meshData.GetVertexCount();
		IndexCount = meshData.GetIndexCount();
		VertexStirde = meshData.GetVertexByteWidth();
	}

	void Draw(ID3D11DeviceContext* context)
	{
		context->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexStirde, &Offset);
		context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(IndexCount, 0, 0);
	}
};