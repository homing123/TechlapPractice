#pragma once
#include "Transform.h"
#include "MeshData.h"
#include "Mesh.h"
#include "ConstantBuffer.h"

class UGameObject
{
public:

private:
	string Name;
	size_t NameKey = 0;
	UTransform Transform;
	FMesh* Mesh = nullptr;
	FTransformConstantBuffer TransformConstantBufferData;
	ID3D11Buffer* TransformConstantBuffer = nullptr;
public:
	UGameObject();
	UGameObject(const string& name, FMesh* pMesh);
	void ChangeName(const string& name);
	UTransform& GetTransform();
	const FMesh* GetMesh() const;
	void Draw(const Matrix& viewProjectionMat);

};