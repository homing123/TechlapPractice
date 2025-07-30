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
	bool bInitialized = false;

	URenderer Renderer;
	vector<unique_ptr<UGameObject>> SceneGameObjects;
	UCamera Camera;
public:
	ID3D11Device* GetDevice() const
	{
		return Renderer.GetDevice();
	}
	ID3D11DeviceContext* GetContext() const
	{
		return Renderer.GetContext();
	}
	const UINT GetScreenWidth() const
	{
		return Renderer.GetScreenWidth();
	}
	const UINT GetScreenHeight() const
	{
		return Renderer.GetScreenHeight();
	}
public:
	bool Init();
	int Run();


	void MakeGameObject(const string& name, FMesh* pMesh);
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

private:
	void Start();
	void Update();
	void Cycle();
	
};