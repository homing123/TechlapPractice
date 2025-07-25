#pragma once

#include "D3DUtil.h"

class UGraphicsPSO
{
private:
	static UGraphicsPSO* LastPSO;
public:
	ID3D11InputLayout* InputLayout = nullptr;
	ID3D11VertexShader* VS = nullptr;
	ID3D11PixelShader* PS = nullptr;

	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11DepthStencilState* DepthStencilState = nullptr;

	D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	void RenderSetting(ID3D11DeviceContext* context);
};