#pragma once
#include "D3DUtil.h"
#include "ConstantBuffer.h"
#include "UTransform.h"
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
	float FovDegree;
	float Near;
	float Far;
	UTransform Transform;
	ID3D11Buffer* CamConstantBuffer;
	FCamConstantBuffer CamConstantBufferData;
public:
	UCamera();
	UTransform& GetTransform();
	const Matrix& GetViewMatix() const;
	const Matrix& GetProjectionMatrix() const;
	const Matrix& GetViewProjectionMatix() const;
	void SetNearFar(const float _near, const float _far);
	void SetFov(const float degree);
	void UpdateConstantBuffer();
};