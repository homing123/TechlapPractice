
#include "App.h"

bool UApp::Init()
{
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

void UApp::Cycle()
{
	Renderer.Render();
}