
#include "App.h"

UApp* UApp::Ins = nullptr;

bool UApp::Init()
{
	Ins = this;
	bool rendererInitialized = Renderer.Init();
	Camera.Init();
	return rendererInitialized;
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
	Renderer.Render(Camera, SceneGameObjects);
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