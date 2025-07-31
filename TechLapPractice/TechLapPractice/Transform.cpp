#include "Transform.h"
#include "GameObject.h"

UTransform::UTransform(UGameObject* pGO) : UComponent(pGO)
{
	const string& name = pGO->GetName();
	cout << "UTransform Creater : " << name << endl;
}
