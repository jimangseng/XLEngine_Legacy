struct VS_out
{
	float4 position : SV_Position;
	float4 color : color;
};

float4 PS (VS_out _in) : SV_Target
{
	float4 output = _in.color;
	
	return output;
}