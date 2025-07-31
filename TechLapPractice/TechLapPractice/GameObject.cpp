#include "GameObject.h"
#include "App.h"


UGameObject::UGameObject(const string& name)
{
	Name = name;
	NameKey = std::hash<string>()(Name);

	Components.emplace_back(make_unique<UTransform>(this));
	cout << "GameObject Creater : " << Name << endl;
}

void UGameObject::EventFunction(const EGameObjectEventFunctionType eventFunctionType)
{
	switch (eventFunctionType)
	{
	case Awake:
		for (unique_ptr<UComponent>& component : Components)
		{
			component.get()->Awake();
		}
		break;
	case OnEnable:
		for (unique_ptr<UComponent>& component : Components)
		{
			component.get()->OnEnable();
		}
		break;
	case Start:
		for (unique_ptr<UComponent>& component : Components)
		{
			component.get()->Start();
		}
		break;
	case Update:
		for (unique_ptr<UComponent>& component : Components)
		{
			component.get()->Update();
		}
		break;
	case OnDisable:
		for (unique_ptr<UComponent>& component : Components)
		{
			component.get()->OnDisable();
		}
		break;
	case OnDestroy:
		for (unique_ptr<UComponent>& component : Components)
		{
			component.get()->OnDestroy();
		}
		break;
	}
}



//void UGameObject::Draw(const Matrix& viewProjectionMat)
//{
//	const Matrix& worldMat = Transform.GetWorldMat();
//	const Matrix& mvpMat = worldMat * viewProjectionMat;
//	const Matrix& invWorldMat = worldMat.Invert();
//	const Matrix& invMVPMat = mvpMat.Invert();
//	TransformConstantBufferData.WorldMatrix = worldMat;
//	TransformConstantBufferData.MVPMatrix = mvpMat;
//	TransformConstantBufferData.InvWorldMatrix = invWorldMat;
//	TransformConstantBufferData.InvMVPMatrix = invMVPMat;
//	D3DUtil::UpdateConstantBuffer(UApp::Ins->GetContext(), TransformConstantBufferData, TransformConstantBuffer);
//	UApp::Ins->GetContext()->VSSetConstantBuffers(TRANSFORM_CONSTANT_BUFFER_SLOT, 1, &TransformConstantBuffer);
//	UApp::Ins->GetContext()->PSSetConstantBuffers(TRANSFORM_CONSTANT_BUFFER_SLOT, 1, &TransformConstantBuffer);
//	UApp::Ins->GetContext()->IASetVertexBuffers(0, 1, &Mesh->VertexBuffer, &Mesh->VertexStirde, &Mesh->Offset);
//	UApp::Ins->GetContext()->IASetIndexBuffer(Mesh->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	UApp::Ins->GetContext()->DrawIndexed(Mesh->IndexCount, 0, 0);
//}