struct VS_in
{
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
	_out.position = float4(_in.position, 1.0f);
	_out.color = _in.color;
	
	return _out;
}	