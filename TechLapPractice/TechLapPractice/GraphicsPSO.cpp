#include "GraphicsPSO.h"

UGraphicsPSO* UGraphicsPSO::LastPSO = nullptr;
void UGraphicsPSO::RenderSetting(ID3D11DeviceContext* context)
{
	if (LastPSO == nullptr)
	{
		context->IASetInputLayout(InputLayout);
		context->VSSetShader(VS, nullptr, 0);
		context->PSSetShader(PS, nullptr, 0);
		context->RSSetState(RasterizerState);
		context->IASetPrimitiveTopology(PrimitiveTopology);
	}
	else
	{
		if (LastPSO->InputLayout != InputLayout)
		{
			context->IASetInputLayout(InputLayout);
		}
		if (LastPSO->VS != VS)
		{
			context->VSSetShader(VS, nullptr, 0);
		}
		if (LastPSO->PS != PS)
		{
			context->PSSetShader(PS, nullptr, 0);
		}
		if (LastPSO->RasterizerState != RasterizerState)
		{
			context->RSSetState(RasterizerState);
		}
		if (LastPSO->PrimitiveTopology != PrimitiveTopology)
		{
			context->IASetPrimitiveTopology(PrimitiveTopology);
		}
	}
	LastPSO = this;
}