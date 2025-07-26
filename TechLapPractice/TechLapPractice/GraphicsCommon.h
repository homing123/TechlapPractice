#pragma once
#include "GraphicsPSO.h"
#include "D3DUtil.h"
#include "Mesh.h"

namespace HMGraphics
{
	extern ID3D11InputLayout* BasicInputLayout;
	extern ID3D11VertexShader* BasicVS;
	extern ID3D11PixelShader* BasicPS;
	extern ID3D11RasterizerState* BasicRasterizerState;
	extern ID3D11BlendState* BasicBlendState;
	extern ID3D11DepthStencilState* BasicDepthStencilState;

	extern UGraphicsPSO BasicPSO;
	extern FMesh QuadMesh;

	void InitGraphics();
	void InitRasterizerState();
	void InitBlendState();
	void InitDepthStencilState();
	void InitShaderAndInputLayout();
	void InitPSO();
	void InitMesh();


}