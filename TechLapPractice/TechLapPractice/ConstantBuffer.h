#pragma once
#ifdef __cplusplus
#define APP_CONSTANT_BUFFER_SLOT 11
#define CAM_CONSTANT_BUFFER_SLOT 12
#define TRANSFORM_CONSTANT_BUFFER_SLOT 13
#else
#define APP_CONSTANT_BUFFER_SLOT b11
#define CAM_CONSTANT_BUFFER_SLOT b12
#define TRANSFORM_CONSTANT_BUFFER_SLOT b13
#endif

#ifdef __cplusplus
#include <directxtk/SimpleMath.h>
using namespace DirectX::SimpleMath;

struct FAppConstantBuffer
{
	float DeltaTime;
	float UnscaledDeltaTime;
	float ElapsedTime;
	float UnscaledElapsedTime;
};
struct FCamConstantBuffer
{
	Matrix ViewMatrix;
	Matrix ProjectionMatrix;
	Matrix ViewProjectionMatrix;
	Matrix InvViewMatrix;
	Matrix InvProjectionMatrix;
	Matrix InvViewProjectionMatrix;
	float CamNear;
	float CamFar;
	UINT ScreenWidth;
	UINT ScreenHieght;
};
struct FTransformConstantBuffer
{
	Matrix WorldMatrix;
	Matrix MVPMatrix;
	Matrix InvWorldMatrix;
	Matrix InvMVPMatrix;
};
#endif