#include "Common.hlsli"

struct VS_Input
{
	float3 ModelPos : POSITION;
	float2 uv : TEXCOORD0;
};
struct PS_Input
{
	float4 ClipPos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

PS_Input mainVS(VS_Input input)
{
	PS_Input output;
    output.ClipPos = mul(MVPMatrix, float4(input.ModelPos, 1));
    output.uv = input.uv;
    return output;
}

float4 mainPS(PS_Input input) : SV_Target
{
	float4 col;

    float clipZ = input.ClipPos.z / input.ClipPos.w;
	col = float4(input.uv, 0.0f, 1.0f);
    //col = float4(clipZ, clipZ, clipZ, 1);
	return col;
}