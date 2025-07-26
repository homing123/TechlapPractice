#include "ConstantBuffer.h"

cbuffer FAppConstantBuffer : register(APP_CONSTANT_BUFFER_SLOT)
{
    float DeltaTime;
    float UnscaledDeltaTime;
    float ElapsedTime;
    float UnscaledElapsedTime;
};
cbuffer FCamConstantBuffer : register(CAM_CONSTANT_BUFFER_SLOT)
{
    Matrix ViewMatrix;
    Matrix ViewProjectionMatrix;
    Matrix InvViewMatrix;
    Matrix InvViewProjectionMatrix;
    float CamNear;
    float CamFar;
    uint ScreenWidth;
    uint ScreenHieght;
};
cbuffer FTransformConstantBuffer : register(TRANSFORM_CONSTANT_BUFFER_SLOT)
{
    Matrix WorldMatrix;
    Matrix InvWorldMatrix;
    Matrix WVPMatrix;
    Matrix InvMVPMatrix;
};