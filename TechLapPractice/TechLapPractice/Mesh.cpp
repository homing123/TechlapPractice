#include "Mesh.h"
#include "App.h"

FMesh::FMesh(const FMeshData& meshData)
{
	D3DUtil::CreateVertexBuffer(meshData.GetVertexValues(), meshData.GetVertexByteWidth(), &VertexBuffer);
	D3DUtil::CreateIndexBuffer(meshData.GetIndices(), &IndexBuffer);
	VertexCount = meshData.GetVertexCount();
	IndexCount = meshData.GetIndexCount();
	VertexStirde = meshData.GetVertexByteWidth();
}

void FMesh::SetMeshData(const FMeshData& meshData)
{
	if (VertexBuffer != nullptr)
	{
		VertexBuffer->Release();
	}
	if (IndexBuffer != nullptr)
	{
		IndexBuffer->Release();
	}
	D3DUtil::CreateVertexBuffer(meshData.GetVertexValues(), meshData.GetVertexByteWidth(), &VertexBuffer);
	D3DUtil::CreateIndexBuffer(meshData.GetIndices(), &IndexBuffer);
	VertexCount = meshData.GetVertexCount();
	IndexCount = meshData.GetIndexCount();
	VertexStirde = meshData.GetVertexByteWidth();
}

