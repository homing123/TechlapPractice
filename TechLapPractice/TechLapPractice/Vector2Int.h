#pragma once

#include "imgui.h"
struct FVector2Int
{
	int x;
	int y;
	FVector2Int() = default;
	FVector2Int(int _x, int _y) : x(_x), y(_y) {}

	inline const bool operator == (const FVector2Int& vt2) const
	{
		return x == vt2.x && y == vt2.y;
	}
	inline const bool operator != (const FVector2Int& vt2) const
	{
		return x != vt2.x || y != vt2.y;
	}
	operator ImVec2() const
	{
		return ImVec2(x, y);
	}
	static FVector2Int Zero;
	static FVector2Int One;
	static FVector2Int UnitX;
	static FVector2Int UnitY;
};