#pragma once
#include "UTransform.h"
#include "MeshData.h"
#include "Mesh.h"

class UGameObject
{
public:

private:
	string Name;
	size_t NameKey;
	UTransform Transform;
	FMesh* Mesh;
public:
	UGameObject(const string& name, FMesh* pMesh)
	{
		Name = name;
		NameKey = std::hash<string>()(Name);
		Mesh = pMesh;
	}
	void ChangeName(const string& name)
	{
		Name = name;
		NameKey = std::hash<string>()(Name);
	}
	UTransform& GetTransform()
	{
		return Transform;
	}
	const FMesh* GetMesh() const
	{
		return Mesh;
	}

};