#pragma once
#include "D3DUtil.h"
#include "ConstantBuffer.h"
#include "directxtk/SimpleMath.h"
#include "Component.h"
#include "Transform.h"
#include <iostream>
using namespace std;
using namespace DirectX::SimpleMath;
using namespace DirectX;

//In View Space
//-z Cam ==> +z
//ndc Near = 0, ndc Far = 1
class UCamera : public UComponent
{
public:
private:
	float FovDegree = 90.0f;
	float Near = 100.0f;
	float Far = 0.1f;
	UTransform* pTransform = nullptr;

	ID3D11Buffer* CamConstantBuffer = nullptr;
	FCamConstantBuffer CamConstantBufferData;
public:
	UCamera(UGameObject* pGO);
	const Matrix GetViewMatix() const;
	const Matrix GetProjectionMatrix() const;
	const Matrix GetViewProjectionMatix() const;
	void SetNearFar(const float _near, const float _far);
	void SetFov(const float degree);
	void UpdateConstantBuffer();
	virtual void DrawInspector() override;
	virtual void Update()
	{
		cout << "Camera  Update" << endl;
	}
};