Texture2D tex : register(t0);

SamplerState samplerState
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = wrap;
	AddressV = wrap;
};

struct VS_out
{
	float4 position : SV_Position;
	float2 uv : TEXCOORD;
};

float4 PS (VS_out _in) : SV_Target
{
	
	float4 output = tex.Sample(samplerState, _in.uv);
	return output;
}