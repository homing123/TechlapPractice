#pragma once

#include "Renderer.h"
#include "GUIManager.h"
#include <unordered_map>
#include "GraphicsCommon.h"
#include "Vector2Int.h"
using namespace HMGraphics;
class UApp
{
public:
	static UApp* Ins;

private:
	bool bInitialized = false;

	URenderer Renderer;
	UGUIManager GUIManager;
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
	const FVector2Int GetWindowSize() const
	{
		return Renderer.GetWindowSize();
	}
	const FVector2Int GetGameSceneSize() const
	{
		return Renderer.GetSceneScreenSize();
	}
public:
	bool Init();
	int Run();

	void MakeGameObject(const string& name, FMesh* pMesh);
	void ResizeWindow(const FVector2Int& windowSize);
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

private:
	void Start();
	void Update();
	void Cycle();
	
};