#include "UCamera.h"
#include "App.h"

UCamera::UCamera()
{
	FovDegree = 90.0f;
	Near = 0.1f;
	Far = 100.0f;
	D3DUtil::CreateConstantBuffer(UApp::Ins->GetDevice(), CamConstantBufferData, &CamConstantBuffer);

}
UTransform& UCamera::GetTransform()
{
	return Transform;
}

const Matrix& UCamera::GetViewMatix() const
{
	//SimpleMath = rowMatrix, 왼쪽에서 오른쪽으로 계산
	//LocalToWorld = v S R T
	//WorldToView = CamTInv CamRInv
	const Vector3& pos = Transform.GetPosition();
	const Vector3& right = Transform.GetRight();
	const Vector3& up = Transform.GetUp();
	const Vector3& forward = Transform.GetForward();
	float rightDotMinusPos = right.Dot(-pos);
	return Matrix
	(
		right.x, up.x, forward.x, 0,
		right.y, up.y, forward.y, 0,
		right.z, up.z, forward.z, 0,
		-pos.Dot(right), -pos.Dot(up), -pos.Dot(forward), 1
	);
}
const Matrix& UCamera::GetProjectionMatrix() const
{
	const UINT screenWidth = UApp::Ins->GetScreenWidth();
	const UINT screenHeight = UApp::Ins->GetScreenHeight();
	const float d = 1 / tan(XMConvertToRadians(FovDegree) * 0.5f);
	const float aspectRCP = (float)screenHeight / (float)screenWidth;
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
const Matrix& UCamera::GetViewProjectionMatix() const
{
	const Vector3& pos = Transform.GetPosition();
	const Vector3& right = Transform.GetRight();
	const Vector3& up = Transform.GetUp();
	const Vector3& forward = Transform.GetForward();
	const UINT screenWidth = UApp::Ins->GetScreenWidth();
	const UINT screenHeight = UApp::Ins->GetScreenHeight();
	const float d = 1 / tan(XMConvertToRadians(FovDegree) * 0.5f);
	const float aspectRCP = (float)screenHeight / (float)screenWidth;
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
	const Matrix& viewMat = GetViewMatix();
	const Matrix& invViewMat = viewMat.Invert();
	const Matrix& projectionMat = GetProjectionMatrix();
	const Matrix& invProjectionMat = projectionMat.Invert();
	const Matrix& viewProjectionMat = GetViewProjectionMatix();
	const Matrix& invViewProjectionMat = viewProjectionMat.Invert();
	CamConstantBufferData.ViewMatrix = viewMat.Transpose();
	CamConstantBufferData.ProjectionMatrix = projectionMat.Transpose();
	CamConstantBufferData.ViewProjectionMatrix = viewProjectionMat.Transpose();
	CamConstantBufferData.InvViewMatrix = invViewMat.Transpose();
	CamConstantBufferData.InvProjectionMatrix = invProjectionMat.Transpose();
	CamConstantBufferData.InvViewProjectionMatrix = invViewProjectionMat.Transpose();

	CamConstantBufferData.CamFar = Far;
	CamConstantBufferData.CamNear = Near;
	CamConstantBufferData.ScreenWidth = UApp::Ins->GetScreenWidth();
	CamConstantBufferData.ScreenHieght = UApp::Ins->GetScreenHeight();

	D3DUtil::UpdateConstantBuffer(UApp::Ins->GetContext(), CamConstantBufferData, CamConstantBuffer);
	UApp::Ins->GetContext()->VSSetConstantBuffers(CAM_CONSTANT_BUFFER_SLOT, 1, &CamConstantBuffer);
}