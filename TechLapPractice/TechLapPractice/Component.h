#pragma once
#include "Inspectable.h"
#include <iostream>

using namespace std;
class UGameObject;
class UComponent : public I_Inspectable
{
public:
protected:
	UGameObject* pGameObject;
private:

public:
	UComponent(UGameObject* pGO);
	virtual void Awake() {};
	virtual void OnEnable() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void OnDisable() {};
	virtual void OnDestroy() {};
private:
};