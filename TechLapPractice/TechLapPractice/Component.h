#pragma once
#include "Inspectable.h"

class UComponent
{
public:
private:
public:
	virtual void Awake() {};
	virtual void OnEnable() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void OnDisable() {};
	virtual void OnDestroy() {};
private:
};