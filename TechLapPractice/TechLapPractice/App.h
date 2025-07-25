#pragma once

#include "Renderer.h"
class UApp
{
public:

private:
	URenderer Renderer;
public:
	bool Init();
	int Run();

private:
	void Cycle();
};