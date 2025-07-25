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

	FConstantBuffer TestCBuffer;

public:
	bool Init();
	void Render();
	void RenderGUI();
private:
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	bool InitWindow();
	bool InitDirect3D();
	bool InitImGui();
};