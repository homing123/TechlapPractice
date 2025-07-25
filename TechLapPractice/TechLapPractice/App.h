#pragma once

#include "Renderer.h"
#include <unordered_map>
#include "GraphicsCommon.h"
using namespace HMGraphics;
class UApp
{
public:
	static UApp* Ins;
private:
	URenderer Renderer;
	vector<unique_ptr<UGameObject>>SceneGameObjects;
public:
	bool Init();
	int Run();

	void MakeGameObject(const string& name, FMesh* pMesh);
	const ID3D11Device* GetDevice() const;
	const ID3D11DeviceContext* GetContext() const;
private:
	void Start();
	void Cycle();
	
};