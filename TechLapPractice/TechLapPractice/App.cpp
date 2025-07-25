
#include "App.h"

UApp* UApp::Ins = nullptr;

bool UApp::Init()
{
	Ins = this;
	return Renderer.Init();
}
int UApp::Run()
{
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
const ID3D11Device* UApp::GetDevice() const
{
	return Renderer.GetDevice();
}
const ID3D11DeviceContext* UApp::GetContext() const
{
	return Renderer.GetContext();
}
void UApp::Cycle()
{
	Renderer.Render();
}
