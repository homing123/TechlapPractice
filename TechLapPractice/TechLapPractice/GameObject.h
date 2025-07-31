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

	//std::enable_if_t : std::enable_if_t<조건, 타입> 조건이true면 타입을 반환, 조건이 false면 컴파일 에러
	//std::is_base_of_v : std::is_base_of_v<Base, Derived> 컴파일 타임에 Base가 Derived의 부모 클래스인지 확인
	//즉 아래는 UComponent가 T의 부모인지 확인 후 맞으면 T*를 반환하는 형태
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