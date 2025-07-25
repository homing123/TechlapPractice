#include "GraphicsCommon.h"

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
}


void HMGraphics::InitGraphics(ID3D11Device* device)
{
	InitRasterizerState(device);
	InitBlendState(device);
	InitDepthStencilState(device);
	InitShaderAndInputLayout(device);
	InitPSO(device);
	InitMesh(device);
}
void HMGraphics::InitRasterizerState(ID3D11Device* device)
{
	D3D11_RASTERIZER_DESC rssDesc = {};
	rssDesc.CullMode = D3D11_CULL_BACK;
	rssDesc.FillMode = D3D11_FILL_SOLID;
	rssDesc.FrontCounterClockwise = false;
	D3DUtil::CreateRasterizerState(device, rssDesc, &BasicRasterizerState);
}
void HMGraphics::InitBlendState(ID3D11Device* device)
{
	
}
void HMGraphics::InitDepthStencilState(ID3D11Device* device)
{

}
void HMGraphics::InitShaderAndInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	D3DUtil::CreateVSAndInputLayout(device, L"BasicShader.hlsl", inputElementDesc, ARRAYSIZE(inputElementDesc), &BasicVS, &BasicInputLayout);
	D3DUtil::CreatePS(device, L"BasicShader.hlsl", &BasicPS);
}
void HMGraphics::InitPSO(ID3D11Device* device)
{
	BasicPSO.InputLayout = BasicInputLayout;
	BasicPSO.VS = BasicVS;
	BasicPSO.PS = BasicPS;
	BasicPSO.RasterizerState = BasicRasterizerState;
}
void HMGraphics::InitMesh(ID3D11Device* device)
{
	QuadMesh = FMesh(device, FMeshData::QuadMeshData);
}