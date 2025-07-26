#pragma once
#include <iostream>
#include <directxtk/SimpleMath.h>
using namespace DirectX::SimpleMath;
using namespace std;
class ULogUtil
{
public:
	void logMatrix(Matrix mat)
	{
		cout << mat.m[0][0] << " " << mat.m[0][1] << " " << mat.m[0][2] << " " << mat.m[0][3] << endl;
		cout << mat.m[1][0] << " " << mat.m[1][1] << " " << mat.m[1][2] << " " << mat.m[1][3] << endl;
		cout << mat.m[2][0] << " " << mat.m[2][1] << " " << mat.m[2][2] << " " << mat.m[2][3] << endl;
		cout << mat.m[3][0] << " " << mat.m[3][1] << " " << mat.m[3][2] << " " << mat.m[3][3] << endl << endl;
	}
};