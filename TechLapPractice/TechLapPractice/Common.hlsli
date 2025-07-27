#include "ConstantBuffer.h"

//Matrix 자료형의 경우 mul 위치에 따라서 내부적으로 transpose 되서 연산되는 것 같다. base는 row 인것 같다.
//기존에 썼던 float4x4의 경우 무조건 column으로 처리되는것 같다 둘다 테스트 필요

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
    Matrix ProjectionMatrix;
    Matrix ViewProjectionMatrix;
    Matrix InvViewMatrix;
    Matrix InvProjectionMatrix;
    Matrix InvViewProjectionMatrix;
    float CamNear;
    float CamFar;
    uint ScreenWidth;
    uint ScreenHieght;
};
cbuffer FTransformConstantBuffer : register(TRANSFORM_CONSTANT_BUFFER_SLOT)
{
    Matrix WorldMatrix;
    Matrix MVPMatrix;
    Matrix InvWorldMatrix;
    Matrix InvMVPMatrix;
};