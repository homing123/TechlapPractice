#pragma once
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "D3DUtil.h"
#include "Vector2Int.h"
class UGUIManager
{
public:
private:
public:
	void InitWindowsTransformAndGetSceneTransform(const FVector2Int& windowSize, FVector2Int& outScenePos, FVector2Int& outSceneSize);
	bool Init(const FVector2Int& windowSize, const HWND& hWnd);
	void Render();
	void ResizeWindowsAndGetScreenSize(const FVector2Int& windowSize, FVector2Int& outScenePos, FVector2Int& outSceneSize);
private:
	void RenderWindows();
	void SetWindowsTransformAndGetSceneTransform(const FVector2Int& windowSize, FVector2Int& outScenePos, FVector2Int& outSceneSize);
	void RenderHierachy();
	void RenderInspector();
	void RenderLog();
	
	float InspectorXRatio = 0.25f;
	float LogYRatio = 0.3f;
	float HierachyXRatio = 0.2f;

	FVector2Int InspectorPos = FVector2Int::Zero;
	FVector2Int InspectorSize = FVector2Int::Zero;
	FVector2Int LogPos = FVector2Int::Zero;
	FVector2Int LogSize = FVector2Int::Zero;
	FVector2Int HierachyPos = FVector2Int::Zero;
	FVector2Int HierachySize = FVector2Int::Zero;

};