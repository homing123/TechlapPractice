#include "D3DUtil.h"
#include "App.h"

void D3DUtil::SetViewport(D3D11_VIEWPORT& viewportInfo, const UINT width, const UINT height)
{
	viewportInfo = {};
	viewportInfo.Width = width;
	viewportInfo.Height = height;
	viewportInfo.TopLeftX = 0;
	viewportInfo.TopLeftY = 0;
	viewportInfo.MinDepth = 0.0f;
	viewportInfo.MaxDepth = 1.0f;
	UApp::Ins->GetContext()->RSSetViewports(1, &viewportInfo);

}

void D3DUtil::ResizeSwapChain()
{

}	
void D3DUtil::CreateSRV(ID3D11Resource* resource, ID3D11ShaderResourceView** resourceSRV)
{

}
void D3DUtil::CreateRTV(ID3D11Resource* resource, ID3D11RenderTargetView** resourceRTV)
{
	D3D11_RENDER_TARGET_VIEW_DESC frameBufferRTVDesc = {};
	frameBufferRTVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	frameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	HRESULT result = UApp::Ins->GetDevice()->CreateRenderTargetView(resource, &frameBufferRTVDesc, resourceRTV);
	if (FAILED(result))
	{
		cout << "Create RenderTargetView Failed" << endl;
		return;
	}
}

bool D3DUtil::CreateDepthStencilTextureAndView(const UINT width, const UINT height, ID3D11Texture2D** depthBuffer, ID3D11DepthStencilView** depthStencilView)
{
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width;
	depthTextureDesc.Height = height;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.SampleDesc.Quality = 0;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0;
	depthTextureDesc.MiscFlags = 0;
	HRESULT hr = UApp::Ins->GetDevice()->CreateTexture2D(&depthTextureDesc, nullptr, depthBuffer);
	if (FAILED(hr))
	{
		cout << "CreateDepthTexture Faield" << endl;
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	hr = UApp::Ins->GetDevice()->CreateDepthStencilView(*depthBuffer, &depthStencilViewDesc, depthStencilView);
	if (FAILED(hr))
	{
		cout << "CreateDepthStencilView Failed" << endl;
		return false;
	}
	return true;
}

void D3DUtil::CreateVSAndInputLayout(const LPCWSTR& fileName, const D3D11_INPUT_ELEMENT_DESC* inputElements, const UINT elementsCount, ID3D11VertexShader** outVS, ID3D11InputLayout** outInputLayout)
{
	ID3DBlob* vsCSO;
	UINT compileFlags = 0;
#if defined(DEBUG) | defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = D3DCompileFromFile(fileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "mainVS", "vs_5_0", compileFlags, 0, &vsCSO, nullptr);
	if (FAILED(hr))
	{
		cout << "VS Compile Failed : " << fileName << endl;
		return;
	}

	hr = UApp::Ins->GetDevice()->CreateVertexShader(vsCSO->GetBufferPointer(), vsCSO->GetBufferSize(), nullptr, outVS);
	if (FAILED(hr))
	{
		cout << "Create VS Failed : " << fileName << endl;
		return;
	}
	hr = UApp::Ins->GetDevice()->CreateInputLayout(inputElements, elementsCount, vsCSO->GetBufferPointer(), vsCSO->GetBufferSize(), outInputLayout);
	if (FAILED(hr))
	{
		cout << "Create InputLayout Failed : " << fileName << endl;
		return;
	}
}
void D3DUtil::CreatePS(const LPCWSTR& fileName, ID3D11PixelShader** outPS)
{
	ID3DBlob* psCSO;
	UINT compileFlags = 0;
#if defined(DEBUG) | defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	HRESULT hr = D3DCompileFromFile(fileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "mainPS", "ps_5_0", compileFlags, 0, &psCSO, nullptr);
	if (FAILED(hr))
	{
		cout << "PS Compile Failed : " << fileName << endl;
		return;
	}
	hr = UApp::Ins->GetDevice()->CreatePixelShader(psCSO->GetBufferPointer(), psCSO->GetBufferSize(), nullptr, outPS);
	if (FAILED(hr))
	{
		cout << "Create PS Failed : " << fileName << endl;
		return;
	}
}


void D3DUtil::CreateVertexBuffer(const vector<float>& vertexValues, const UINT vertexByteWidth, ID3D11Buffer** outVertexBuffer)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = vertexValues.size() * sizeof(float);
	D3D11_SUBRESOURCE_DATA vertexBufferSRD;
	vertexBufferSRD.pSysMem = vertexValues.data();

	HRESULT hr = UApp::Ins->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferSRD, outVertexBuffer);
	if (FAILED(hr))
	{
		cout << "Create Vertex Buffer Failed" << endl;
		return;
	}
}
void D3DUtil::CreateIndexBuffer(const vector<int32_t>& indices, ID3D11Buffer** outIndexBuffer)
{
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = indices.size() * sizeof(int32_t);
	D3D11_SUBRESOURCE_DATA indexBufferSRD;
	indexBufferSRD.pSysMem = indices.data();

	HRESULT hr = UApp::Ins->GetDevice()->CreateBuffer(&indexBufferDesc, &indexBufferSRD, outIndexBuffer);
	if (FAILED(hr))
	{
		cout << "Create Index Buffer Failed" << endl;
		return;
	}
}

