#pragma once

#include "Renderer.h"
#include <unordered_map>
class UApp
{
public:
	static UApp* Ins;
private:
	URenderer Renderer;
	unordered_map<size_t, unique_ptr<UGameObject>> SceneGameObjectMap;
public:
	bool Init();
	int Run();

	void MakeGameObject();
	const ID3D11Device* GetDevice() const;
	const ID3D11DeviceContext* GetContext() const;
private:
	void Cycle();
	
};