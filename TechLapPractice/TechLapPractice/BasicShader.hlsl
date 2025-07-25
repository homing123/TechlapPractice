cbuffer constants : register(b0)
{
	float4 Color;
}

struct VS_Input
{
	float4 ModelPos : POSITION;
	float4 Color : COLOR;
};
struct PS_Input
{
	float4 ClipPos : SV_POSITION;
	float4 Color : COLOR;
};

PS_Input mainVS(VS_Input input)
{
	PS_Input output;
	output.ClipPos = input.ModelPos;
	output.Color = input.Color;
	return output;
}

float4 mainPS(PS_Input input) : SV_Target
{
	float4 col;
	col = float4(Color.rgb, 1.0f);
	return col;
}