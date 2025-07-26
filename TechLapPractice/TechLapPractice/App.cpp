
#include "App.h"

UApp* UApp::Ins = nullptr;

bool UApp::Init()
{
	Ins = this;
	return Renderer.Init();
}
void UApp::Start() 
{
	MakeGameObject("TestObject", &QuadMesh);
}
void UApp::Cycle()
{
	Renderer.Render(SceneGameObjects);
}

void UApp::MakeGameObject(const string& name, FMesh* pMesh)
{
	SceneGameObjects.emplace_back(make_unique<UGameObject>(name, pMesh));
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