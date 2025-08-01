#include "GraphicsCommon.h"
#include "App.h"

namespace HMGraphics
{
	ID3D11InputLayout* BasicInputLayout;
	ID3D11VertexShader* BasicVS;
	ID3D11PixelShader* BasicPS;
	ID3D11RasterizerState* BasicRasterizerState;
	ID3D11BlendState* BasicBlendState;
	ID3D11DepthStencilState* BasicDepthStencilState;

	UGraphicsPSO BasicPSO;
	FMesh QuadMesh;
	FMesh CubeMesh;
}


void HMGraphics::InitGraphics()
{
	InitRasterizerState();
	InitBlendState();
	InitDepthStencilState();
	InitShaderAndInputLayout();
	InitPSO();
	InitMesh();
}
void HMGraphics::InitRasterizerState()
{
	D3D11_RASTERIZER_DESC rssDesc = {};
	rssDesc.CullMode = D3D11_CULL_BACK;
	rssDesc.FillMode = D3D11_FILL_SOLID;
	rssDesc.FrontCounterClockwise = false;
	UApp::Ins->GetDevice()->CreateRasterizerState(&rssDesc, &BasicRasterizerState);
}
void HMGraphics::InitBlendState()
{
	
}
void HMGraphics::InitDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilStateDesc.StencilEnable = false;
	UApp::Ins->GetDevice()->CreateDepthStencilState(&depthStencilStateDesc, &BasicDepthStencilState);
}
void HMGraphics::InitShaderAndInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	D3DUtil::CreateVSAndInputLayout(L"BasicShader.hlsl", inputElementDesc, ARRAYSIZE(inputElementDesc), &BasicVS, &BasicInputLayout);
	D3DUtil::CreatePS(L"BasicShader.hlsl", &BasicPS);
}
void HMGraphics::InitPSO()
{
	BasicPSO.InputLayout = BasicInputLayout;
	BasicPSO.VS = BasicVS;
	BasicPSO.PS = BasicPS;
	BasicPSO.RasterizerState = BasicRasterizerState;
	BasicPSO.DepthStencilState = BasicDepthStencilState;
}
void HMGraphics::InitMesh()
{
	QuadMesh = FMesh(FMeshData::QuadMeshData);
	CubeMesh = FMesh(FMeshData::CubeMeshData);
}