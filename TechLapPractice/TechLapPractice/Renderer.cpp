#include "Renderer.h"
#include "App.h"


bool URenderer::Init()
{
	if (InitWindow() == false)
	{
		return false;
	}
	if (InitDirect3D() == false)
	{
		return false;
	}
	if (InitImGui() == false)
	{
		return false;
	}
	InitGraphics();	

	return true;
}

void URenderer::Render(UCamera& camera, const vector<unique_ptr<UGameObject>>& sceneGameObjects)
{
	camera.UpdateConstantBuffer();
	Matrix viewProjectionMat = camera.GetViewProjectionMatix();

	Context->ClearRenderTargetView(FrameBufferRTV, ClearColor);

	//depth 있는버전
	Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	Context->OMSetRenderTargets(1, &FrameBufferRTV, DepthStencilView);

	//depth 없는버전
	//Context->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);

	Context->RSSetViewports(1, &ViewportInfo);
	Context->OMSetBlendState(nullptr, nullptr, 0xffffffff);
	Context->PSSetConstantBuffers(0, 1, &ConstantBuffer);
	BasicPSO.RenderSetting(Context);
	int sceneGameObjectCount = sceneGameObjects.size();
	for (int i = 0; i < sceneGameObjectCount; i++)
	{
		sceneGameObjects[i].get()->Draw(viewProjectionMat);
	}
	RenderGUI();
	SwapChain->Present(1, 0); // 1: VSync 활성화
}

void URenderer::RenderGUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("GUI Window");
	ImGui::Text("Test");

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void URenderer::ResizeWindow(UINT width, UINT height)
{
	ScreenWidth = width;
	ScreenHeight = height;
	FrameBufferRTV->Release();
	DepthBuffer->Release();
	FrameBuffer->Release();
	//ResizeBuffers 에서 DXGI_FORMAT_UNKNOWN는 기존 포맷 유지
	SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
	HRESULT result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

	D3DUtil::CreateRTV(FrameBuffer, &FrameBufferRTV);

	D3DUtil::SetViewport(ViewportInfo, ScreenWidth, ScreenHeight);
	D3DUtil::CreateDepthStencilTextureAndView(ScreenWidth, ScreenHeight, &DepthBuffer, &DepthStencilView);
}




bool URenderer::InitWindow()
{
	//https://shintesh.tistory.com/18
	//HInstance = 창 종류의 구분을 위한 값
	//HWND = 창 구분을 위한 값
	//ex HInstance = 메모장 2개켜면 같은값, HWND 는 다른값
	
	const WCHAR windowName[] = L"HMWindow";
	const WCHAR titleName[] = L"Title";

	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	wndClass.lpfnWndProc = UApp::MsgProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hIcon = LoadIcon(wndClass.hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(wndClass.hInstance, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = windowName;
	wndClass.hIconSm = nullptr;
	if (RegisterClassEx(&wndClass) == false)
	{
		cout << "RegisterClassEx is Failed in InitWindow" << endl;
		return false;
	}
	DWORD WindowStyle = WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW;
	int WindowPosX = CW_USEDEFAULT;
	int WindowPosY = CW_USEDEFAULT;

	RECT rect = { 0, 0, ScreenWidth, ScreenHeight };
	AdjustWindowRect(&rect, WindowStyle, false);

	HWnd = CreateWindowExW(0, windowName, titleName, WindowStyle,
		WindowPosX, WindowPosY, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wndClass.hInstance, nullptr);

	if (HWnd == nullptr)
	{
		cout << "InitWindow Failed" << endl;
		return false;
	}

	ShowWindow(HWnd, SW_SHOWDEFAULT);
	UpdateWindow(HWnd);
	return true;

}

bool URenderer::InitDirect3D()
{
	const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
	const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL featureLevel;

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	createDeviceFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	//if (FAILED(D3D11CreateDevice
	//(
	//	nullptr,
	//	driverType,
	//	0,
	//	createDeviceFlags,
	//	featureLevels,
	//	ARRAYSIZE(featureLevels),
	//	D3D11_SDK_VERSION,
	//	&Device,
	//	&featureLevel,
	//	&Context
	//)))
	//{
	//	cout << "D3D11CreateDevice Failed" << endl;
	//	return false;
	//}

	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.BufferDesc.Width = ScreenWidth;
	swapchainDesc.BufferDesc.Height = ScreenHeight;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.Windowed = true;
	swapchainDesc.OutputWindow = HWnd;
	swapchainDesc.BufferCount = 2;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 
		createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), 
		D3D11_SDK_VERSION, &swapchainDesc, &SwapChain,
		&Device, &featureLevel, &Context)))
	{
		cout << "D3D11CreateDeviceAndSwapChain Failed" << endl;
		return false;
	}
	
	HRESULT result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
	if (FAILED(result))
	{
		cout << "Get SwapChain Buffer Failed" << endl;
		return false;
	}
	D3DUtil::SetViewport(ViewportInfo, ScreenWidth, ScreenHeight);
	D3DUtil::CreateRTV(FrameBuffer, &FrameBufferRTV);
	D3DUtil::CreateDepthStencilTextureAndView(ScreenWidth, ScreenHeight, &DepthBuffer, &DepthStencilView);

	
	
	return true;
}

bool URenderer::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(ScreenWidth, ScreenHeight);
	if (ImGui_ImplWin32_Init(HWnd) == false)
	{
		return false;
	}
	if (ImGui_ImplDX11_Init(Device, Context) == false)
	{
		return false;
	}
	return true;
}