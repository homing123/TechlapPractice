#include "Renderer.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	Context->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);
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


LRESULT CALLBACK URenderer::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DISPLAYCHANGE:
		break;
	case WM_SIZE:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	default : 
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
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
	wndClass.lpfnWndProc = MsgProc;
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
	D3DUtil::SetViewport(ViewportInfo, ScreenWidth, ScreenHeight);
	
	HRESULT result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
	if (FAILED(result))
	{
		cout << "Get SwapChain Buffer Failed" << endl;
		return false;
	}

	D3D11_RENDER_TARGET_VIEW_DESC frameBufferRTVDesc = {};
	frameBufferRTVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	frameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	result = Device->CreateRenderTargetView(FrameBuffer, &frameBufferRTVDesc, &FrameBufferRTV);
	if (FAILED(result))
	{
		cout << "Create RenderTargetView Failed" << endl;
		return false;
	}
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