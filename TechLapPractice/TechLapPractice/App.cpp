
#include "App.h"

UApp* UApp::Ins = nullptr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool UApp::Init()
{
	Ins = this;
	FVector2Int scenePos;
	FVector2Int sceneSize;
	GUIManager.InitWindowsTransformAndGetSceneTransform(Renderer.GetWindowSize(), scenePos, sceneSize);
	if (Renderer.Init(scenePos, sceneSize) == false)
	{
		return false;
	}
	if (GUIManager.Init(Renderer.GetWindowSize(), Renderer.GetHWND()) == false)
	{
		return false;
	}
	Camera.Init();
	bInitialized = true;
	cout << "AppInit Success" << endl;
	return true;
}
void UApp::Start() 
{
	MakeGameObject("TestObject", &CubeMesh);
	MakeGameObject("Test2", &CubeMesh);
	SceneGameObjects[0].get()->GetTransform().SetPosition(Vector3(2.0f, 0.0f, 1.01f));
	Camera.GetTransform().SetPosition(Vector3(0, 0, -5.0f));
}



void UApp::Update()
{
	static Vector3 curPos = Vector3(0.0f, 0.0f, 6.0f);
	curPos.x += 0.02f;

	

}
void UApp::Cycle()
{
	Update();
	Renderer.RenderGameScene(Camera, SceneGameObjects);
	GUIManager.Render();
	Renderer.SwapChainPresent();
}

void UApp::MakeGameObject(const string& name, FMesh* pMesh)
{
	SceneGameObjects.emplace_back(make_unique<UGameObject>(name, pMesh));
}	

void UApp::ResizeWindow(const FVector2Int& windowSize)
{
	FVector2Int scenePos;
	FVector2Int sceneSize;
	GUIManager.ResizeWindowsAndGetScreenSize(windowSize, scenePos, sceneSize);
	Renderer.ResizeWindow(windowSize, scenePos, sceneSize);
}


int UApp::Run()
{
	Start();
	bool IsExit = false;
	while (IsExit == false)
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				IsExit = true;
				break;
			}
		}
		Cycle();
	}
	return 0;
}

LRESULT CALLBACK UApp::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	{
		if (UApp::Ins->bInitialized)
		{
			UINT screenWidth = LOWORD(lParam);
			UINT screenHeight = HIWORD(lParam);
			UApp::Ins->ResizeWindow(FVector2Int(screenWidth, screenHeight));
		}
	}
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
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}