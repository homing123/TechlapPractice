#pragma once
#include "D3DUtil.h"
#include "ConstantBuffer.h"
#include "Transform.h"
#include "directxtk/SimpleMath.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//In View Space
//-z Cam ==> +z
//ndc Near = 0, ndc Far = 1
class UCamera
{
public:
private:
	float FovDegree = 90.0f;
	float Near = 100.0f;
	float Far = 0.1f;
	UTransform Transform;
	ID3D11Buffer* CamConstantBuffer = nullptr;
	FCamConstantBuffer CamConstantBufferData;
public:
	void Init();
	UTransform& GetTransform();
	const Matrix GetViewMatix() const;
	const Matrix GetProjectionMatrix() const;
	const Matrix GetViewProjectionMatix() const;
	void SetNearFar(const float _near, const float _far);
	void SetFov(const float degree);
	void UpdateConstantBuffer();
};