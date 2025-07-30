#include "GUIManager.h"
#include "App.h"

void UGUIManager::InitWindowsTransformAndGetSceneTransform(const FVector2Int& windowSize, FVector2Int& outScenePos, FVector2Int& outSceneSize)
{
	SetWindowsTransformAndGetSceneTransform(windowSize, outScenePos, outSceneSize);
}
bool UGUIManager::Init(const FVector2Int& windowSize, const HWND& hWnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = windowSize;
	io.IniFilename = nullptr; //창 크기 위치 로컬파일에 저장 비활성화
	if (ImGui_ImplWin32_Init(hWnd) == false)
	{
		return false;
	}
	if (ImGui_ImplDX11_Init(UApp::Ins->GetDevice(), UApp::Ins->GetContext()) == false)
	{
		return false;
	}

	return true;
}

void UGUIManager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	RenderWindows();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}	
void UGUIManager::ResizeWindowsAndGetScreenSize(const FVector2Int& windowSize, FVector2Int& outScenePos, FVector2Int& outSceneSize)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = windowSize;
	SetWindowsTransformAndGetSceneTransform(windowSize, outScenePos, outSceneSize);
}
void UGUIManager::RenderWindows() 
{
	RenderInspector();
	RenderLog();
	RenderHierachy();
}
void UGUIManager::SetWindowsTransformAndGetSceneTransform(const FVector2Int& windowSize, FVector2Int& outScenePos, FVector2Int& outSceneSize)
{
	int inspectorWidth = int(windowSize.x * InspectorXRatio);
	InspectorSize = FVector2Int(inspectorWidth, windowSize.y);
	InspectorPos = FVector2Int(windowSize.x - inspectorWidth, 0);

	int logHeight = (int)(windowSize.y * LogYRatio);
	LogSize = FVector2Int(windowSize.x - InspectorSize.x, logHeight);
	LogPos = FVector2Int(0, windowSize.y - LogSize.y);

	int hierachyWidth = (int)(windowSize.x * HierachyXRatio);
	HierachySize = FVector2Int(hierachyWidth, windowSize.y - logHeight);
	HierachyPos = FVector2Int(0, 0);

	outScenePos = FVector2Int(HierachySize.x, 0);
	outSceneSize = FVector2Int(windowSize.x - HierachySize.x - InspectorSize.x, windowSize.y - LogSize.y);
}

void UGUIManager::RenderInspector()
{
	ImGui::SetNextWindowPos(InspectorPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(InspectorSize, ImGuiCond_Always);

	ImGui::Begin("Inspector");
	ImGui::Text("Inspector Text");
	
	ImGui::End();
}
void UGUIManager::RenderLog()
{
	ImGui::SetNextWindowPos(LogPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(LogSize, ImGuiCond_Always);

	ImGui::Begin("Log");
	ImGui::Text("Log Text");

	ImGui::End();
}

void UGUIManager::RenderHierachy()
{
	ImGui::SetNextWindowPos(HierachyPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(HierachySize, ImGuiCond_Always);

	ImGui::Begin("Hierachy");
	ImGui::Text("Hierachy Text");

	ImGui::End();
}

