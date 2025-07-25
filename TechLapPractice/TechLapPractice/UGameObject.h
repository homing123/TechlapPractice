#pragma once
#include "UTransform.h"
#include "MeshData.h"
#include "Mesh.h"
class UGameObject
{
public:
private:
	UTransform Transform;
	FMesh Mesh;
public:
	UGameObject(ID3D11Device* device, const FMeshData& meshData)
	{
		Mesh.SetMeshData(device, meshData);
	}
	UTransform& GetTransform()
	{
		return Transform;
	}

};