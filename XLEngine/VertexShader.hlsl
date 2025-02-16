cbuffer VS_constantBuffer : register(b0)
{
	matrix WVP;
}

struct VS_in
{
	float3 positionL : Localposition;
	float2 uv : TEXCOORD;
};

struct VS_out
{
	float4 position : SV_Position;
	float2 uv : TEXCOORD;
};
VS_out VS (VS_in _in)
{
	VS_out _out;
	_out.position = mul(WVP, float4(_in.positionL, 1.0f) );
	_out.uv = _in.uv;
	
	return _out;
}	