#include "ConstantBuffer.h"

//Matrix �ڷ����� ��� mul ��ġ�� ���� ���������� transpose �Ǽ� ����Ǵ� �� ����. base�� row �ΰ� ����.
//������ ��� float4x4�� ��� ������ column���� ó���Ǵ°� ���� �Ѵ� �׽�Ʈ �ʿ�

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