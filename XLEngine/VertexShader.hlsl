cbuffer VS_constantBuffer : register(b0)
{
	matrix world;
}

struct VS_in
{
	float3 positionL : Localposition;
	float3 position : Position;
	float4 color : color;
};

struct VS_out
{
	float4 position : SV_Position;
	float4 color : color;
};
VS_out VS (VS_in _in)
{
	VS_out _out;
	_out.position = mul(float4(_in.positionL, 1.0f), world);
	_out.color = _in.color;
	
	return _out;
}	