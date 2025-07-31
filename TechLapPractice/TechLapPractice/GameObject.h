#pragma once
#include "Transform.h"
#include "Component.h"
#include <vector>

enum EGameObjectEventFunctionType
{
	Awake,
	OnEnable,
	Start,
	Update,
	OnDisable,
	OnDestroy
};
using namespace std;

class UGameObject
{
public:

private:
	string Name;
	size_t NameKey = 0;
	vector<unique_ptr<UComponent>> Components;

public:
	UGameObject(const string& name);
	void EventFunction(const EGameObjectEventFunctionType eventFunctionType);
	


public:
	UTransform* GetTransform() const
	{
		return dynamic_cast<UTransform*>(Components[0].get());
	}
	void SetName(const string& name)
	{
		Name = name;
		NameKey = std::hash<string>()(Name);
	}
	const string& GetName() const
	{
		return Name;
	}

	//std::enable_if_t : std::enable_if_t<����, Ÿ��> ������true�� Ÿ���� ��ȯ, ������ false�� ������ ����
	//std::is_base_of_v : std::is_base_of_v<Base, Derived> ������ Ÿ�ӿ� Base�� Derived�� �θ� Ŭ�������� Ȯ��
	//�� �Ʒ��� UComponent�� T�� �θ����� Ȯ�� �� ������ T*�� ��ȯ�ϴ� ����
	template<typename T>
	typename std::enable_if_t<std::is_base_of_v<UComponent, T>, T*> AddComponent()
	{
		unique_ptr<T> component = make_unique<T>(this);
		Components.push_back(move(component));
		T* ptr = component.get();
		cout << "AddComponent " << typeid(T).name() << " : " << Name << endl;
		return ptr;
	}
};