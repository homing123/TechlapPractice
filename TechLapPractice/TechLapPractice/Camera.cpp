#include "Camera.h"
#include "App.h"
#include "GameObject.h"

UCamera::UCamera(UGameObject* pGO) : UComponent(pGO)
{
	const string& name = pGO->GetName();
	cout << "UCamera Creater : " << name << endl;

	FovDegree = 90.0f;
	Near = 0.01f;
	Far = 100.0f;
	D3DUtil::CreateConstantBuffer(UApp::Ins->GetDevice(), CamConstantBufferData, &CamConstantBuffer);
	UApp::Ins->GetContext()->VSSetConstantBuffers(CAM_CONSTANT_BUFFER_SLOT, 1, &CamConstantBuffer);
	UApp::Ins->GetContext()->PSSetConstantBuffers(CAM_CONSTANT_BUFFER_SLOT, 1, &CamConstantBuffer);
	pTransform = pGameObject->GetTransform();
}

const Matrix UCamera::GetViewMatix() const
{
	//SimpleMath = rowMatrix, 왼쪽에서 오른쪽으로 계산
	//LocalToWorld = v S R T
	//WorldToView = CamTInv CamRInv
	const Vector3& pos = pTransform->GetPosition();
	const Vector3& right = pTransform->GetRight();
	const Vector3& up = pTransform->GetUp();
	const Vector3& forward = pTransform->GetForward();
	return Matrix
	(
		right.x, up.x, forward.x, 0,
		right.y, up.y, forward.y, 0,
		right.z, up.z, forward.z, 0,
		-pos.Dot(right), -pos.Dot(up), -pos.Dot(forward), 1
	);
}
const Matrix UCamera::GetProjectionMatrix() const
{
	const FVector2Int windowSize = UApp::Ins->GetGameSceneSize();
	const float d = 1 / tan(XMConvertToRadians(FovDegree) * 0.5f);
	const float aspectRCP = (float)windowSize.y / (float)windowSize.x;
	const float farMinusNearRCP = 1 / (Far - Near);
	const float m = Far * farMinusNearRCP;
	const float n = -Far * Near * farMinusNearRCP;
	return Matrix
	(
		d * aspectRCP, 0, 0, 0,
		0, d, 0, 0,
		0, 0, m, 1,
		0, 0, n, 0
	);
}
const Matrix UCamera::GetViewProjectionMatix() const
{
	const Vector3& pos = pTransform->GetPosition();
	const Vector3& right = pTransform->GetRight();
	const Vector3& up = pTransform->GetUp();
	const Vector3& forward = pTransform->GetForward();
	const FVector2Int windowSize = UApp::Ins->GetGameSceneSize();
	const float d = 1 / tan(XMConvertToRadians(FovDegree) * 0.5f);
	const float aspectRCP = (float)windowSize.y / (float)windowSize.x;
	const float farMinusNearRCP = 1 / (Far - Near);
	const float m = Far * farMinusNearRCP;
	const float n = -Far * Near * farMinusNearRCP;

	return Matrix
	(
		right.x * d * aspectRCP, up.x * d, forward.x * m, forward.x,
		right.y * d * aspectRCP, up.y * d, forward.y * m, forward.y,
		right.z * d * aspectRCP, up.z * d, forward.z * m, forward.z,
		-right.Dot(pos) * d * aspectRCP, -up.Dot(pos) * d, -forward.Dot(pos) * m + n, -forward.Dot(pos)
	);
}

void UCamera::SetNearFar(const float _near, const float _far)
{
	Near = max(min(_far - 0.1f, _near), 0.01f);
	Far = max(min(9999.0f, _far), _near + 0.01f);
}
void UCamera::SetFov(const float degree)
{
	FovDegree = max(min(179, degree), 1);
}
void UCamera::UpdateConstantBuffer()
{
	const Matrix viewMat = GetViewMatix();
	const Matrix invViewMat = GetViewMatix().Invert();
	const Matrix projectionMat = GetProjectionMatrix();
	const Matrix invProjectionMat = projectionMat.Invert();
	const Matrix viewProjectionMat = GetViewProjectionMatix();
	const Matrix invViewProjectionMat = viewProjectionMat.Invert();
	CamConstantBufferData.ViewMatrix = viewMat;
	CamConstantBufferData.ProjectionMatrix = projectionMat;
	CamConstantBufferData.ViewProjectionMatrix = viewProjectionMat;
	CamConstantBufferData.InvViewMatrix = invViewMat;
	CamConstantBufferData.InvProjectionMatrix = invProjectionMat;
	CamConstantBufferData.InvViewProjectionMatrix = invViewProjectionMat;

	CamConstantBufferData.CamFar = Far;
	CamConstantBufferData.CamNear = Near;
	CamConstantBufferData.ScreenWidth = UApp::Ins->GetGameSceneSize().x;
	CamConstantBufferData.ScreenHieght = UApp::Ins->GetGameSceneSize().y;

	D3DUtil::UpdateConstantBuffer(UApp::Ins->GetContext(), CamConstantBufferData, CamConstantBuffer);
}

void UCamera::DrawInspector()
{

}
