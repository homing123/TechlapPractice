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

	void InitGraphics(ID3D11Device* device);
	void InitRasterizerState(ID3D11Device* device);
	void InitBlendState(ID3D11Device* device);
	void InitDepthStencilState(ID3D11Device* device);
	void InitShaderAndInputLayout(ID3D11Device* device);
	void InitPSO(ID3D11Device* device);
	void InitMesh(ID3D11Device* device);


}