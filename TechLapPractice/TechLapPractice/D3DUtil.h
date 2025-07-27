#pragma once
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>

using namespace std;
class D3DUtil
{
public:
	template<typename T>
	static void CreateConstantBuffer(ID3D11Device* device, const T& cBufferData, ID3D11Buffer** cBuffer)
	{
		D3D11_BUFFER_DESC cBufferDesc = {};
		cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		cBufferDesc.ByteWidth = sizeof(cBufferData);

		D3D11_SUBRESOURCE_DATA cBufferSRD = {};
		cBufferSRD.pSysMem = &cBufferData;

		HRESULT hr = device->CreateBuffer(&cBufferDesc, &cBufferSRD, cBuffer);
		if (FAILED(hr))
		{
			cout << "CreateConstantBuffer Failed" << endl;
			return;
		}
	}
	template<typename T>
	static void UpdateConstantBuffer(ID3D11DeviceContext* context, const T& cBufferData, ID3D11Buffer* cBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE cBufferMSR = {};
		HRESULT hr = context->Map(cBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &cBufferMSR);
		if (FAILED(hr))
		{
			cout << "UpdateConstantBuffer Failed" << endl;
			return;
		}
		memcpy(cBufferMSR.pData, &cBufferData, sizeof(T));
		context->Unmap(cBuffer, 0);
	}

	static void SetViewport(D3D11_VIEWPORT& viewportInfo, const UINT width, const UINT height);
	static void CreateVSAndInputLayout(const LPCWSTR& fileName, const D3D11_INPUT_ELEMENT_DESC* inputElements, const UINT elementsCount, ID3D11VertexShader** outVS, ID3D11InputLayout** outInputLayout);
	static void CreatePS(const LPCWSTR& fileName, ID3D11PixelShader** outPS);
	static void CreateVertexBuffer(const vector<float>& vertexValues, const UINT vertexByteWidth, ID3D11Buffer** outVertexBuffer);
	static void CreateIndexBuffer(const vector<int>& indices, ID3D11Buffer** outIndexBuffer);
};