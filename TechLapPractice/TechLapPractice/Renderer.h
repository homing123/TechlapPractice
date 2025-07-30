#pragma once
#include "D3DUtil.h"

#include <Windows.h>
#include "ConstantBuffer.h"
#include "GraphicsPSO.h"
#include "GraphicsCommon.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Vector2Int.h"

using namespace HMGraphics;

class URenderer
{
public:

private:
	FVector2Int WindowSize = FVector2Int(1200, 800);
	FVector2Int ScenePos = FVector2Int::Zero;
	FVector2Int SceneSize = FVector2Int::Zero;
	float ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	HWND HWnd;

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;

	ID3D11Texture2D* DepthBuffer = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;
	D3D11_VIEWPORT GameSceneViewport;
	ID3D11VertexShader* BasicVS;
	ID3D11PixelShader* BasicPS;
	ID3D11InputLayout* BasicInputLayout;


public:
	bool Init(const FVector2Int& scenePos, const FVector2Int& sceneSize);
	void RenderGameScene(UCamera& camera,  const vector<unique_ptr<UGameObject>>& sceneGameObjects);
	void SwapChainPresent();
public:
	ID3D11Device* GetDevice() const
	{
		return Device;
	}

	ID3D11DeviceContext* GetContext() const
	{
		return Context;
	}
	const HWND& GetHWND()
	{
		return HWnd;
	}

	const FVector2Int& GetWindowSize() const
	{
		return WindowSize;
	}
	const FVector2Int& GetSceneScreenPos() const
	{
		return ScenePos;
	}
	const FVector2Int& GetSceneScreenSize() const
	{
		return SceneSize;
	}
	void ResizeWindow(const FVector2Int& windowSize, const FVector2Int& scenePos, const FVector2Int& sceneSize);
	void SetGameSceneViewport();
private:
	bool InitWindow();
	bool InitDirect3DAndCreateSwapChainBuffer();
};