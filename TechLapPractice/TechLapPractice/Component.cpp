#include "Component.h"
#include "GameObject.h"

UComponent::UComponent(UGameObject* pGO)
{
	pGameObject = pGO;
	const string& name = pGO->GetName();
	cout << "UComponent Creater : " << name << endl;
}