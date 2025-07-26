#pragma once
#include "D3DUtil.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <Windows.h>
#include "ConstantBuffer.h"
#include "GraphicsPSO.h"
#include "GraphicsCommon.h"
#include "Mesh.h"
#include "UGameObject.h"
#include "UTransform.h"

using namespace HMGraphics;

class URenderer
{
public:

private:
	UINT ScreenWidth = 1200;
	UINT ScreenHeight = 800;
	float ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	HWND HWnd;

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;
	D3D11_VIEWPORT ViewportInfo;
	ID3D11VertexShader* BasicVS;
	ID3D11PixelShader* BasicPS;
	ID3D11InputLayout* BasicInputLayout;

public:
	bool Init();
	void Render(const vector<unique_ptr<UGameObject>>& sceneGameObjects);
	void RenderGUI();
public:
	ID3D11Device* GetDevice() const
	{
		return Device;
	}

	ID3D11DeviceContext* GetContext() const
	{
		return Context;
	}

	const UINT GetScreenWidth() const
	{
		return ScreenWidth;
	}
	const UINT GetScreenHeight() const
	{
		return ScreenHeight;
	}
private:
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	bool InitWindow();
	bool InitDirect3D();
	bool InitImGui();
};