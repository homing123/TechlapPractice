#include "GameObject.h"
#include "App.h"

UGameObject::UGameObject()
{
	cout << "gameobject 持失" << endl;
}
UGameObject::UGameObject(const string& name, FMesh* pMesh)
{
	Name = name;
	NameKey = std::hash<string>()(Name);
	Mesh = pMesh;
	D3DUtil::CreateConstantBuffer(UApp::Ins->GetDevice(), TransformConstantBufferData, &TransformConstantBuffer);
	cout << "gameobject 持失2" << endl;
}
void UGameObject::ChangeName(const string& name)
{
	Name = name;
	NameKey = std::hash<string>()(Name);
}
UTransform& UGameObject::GetTransform()
{
	return Transform;
}
const FMesh* UGameObject::GetMesh() const
{
	return Mesh;
}
void UGameObject::Draw(const Matrix& viewProjectionMat)
{
	const Matrix& worldMat = Transform.GetWorldMat();
	const Matrix& mvpMat = worldMat * viewProjectionMat;
	const Matrix& invWorldMat = worldMat.Invert();
	const Matrix& invMVPMat = mvpMat.Invert();
	TransformConstantBufferData.WorldMatrix = worldMat;
	TransformConstantBufferData.MVPMatrix = mvpMat;
	TransformConstantBufferData.InvWorldMatrix = invWorldMat;
	TransformConstantBufferData.InvMVPMatrix = invMVPMat;
	D3DUtil::UpdateConstantBuffer(UApp::Ins->GetContext(), TransformConstantBufferData, TransformConstantBuffer);
	UApp::Ins->GetContext()->VSSetConstantBuffers(TRANSFORM_CONSTANT_BUFFER_SLOT, 1, &TransformConstantBuffer);
	UApp::Ins->GetContext()->PSSetConstantBuffers(TRANSFORM_CONSTANT_BUFFER_SLOT, 1, &TransformConstantBuffer);
	UApp::Ins->GetContext()->IASetVertexBuffers(0, 1, &Mesh->VertexBuffer, &Mesh->VertexStirde, &Mesh->Offset);
	UApp::Ins->GetContext()->IASetIndexBuffer(Mesh->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	UApp::Ins->GetContext()->DrawIndexed(Mesh->IndexCount, 0, 0);
}