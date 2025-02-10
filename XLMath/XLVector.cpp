#include "XLVector.h"

using namespace DirectX;
using namespace XL::Math;


Vector3&& Vector3::operator+ (const Vector3& _rhs)
{
	DirectX::XMFLOAT3 f;
	XMStoreFloat3(&f, (DirectX::XMLoadFloat3(&floats) + DirectX::XMLoadFloat3(&_rhs.floats)));

	return Vector3(f);
}

Vector3&& Vector3::operator- (const Vector3& _rhs)
{
	DirectX::XMFLOAT3 f;
	XMStoreFloat3(&f, (DirectX::XMLoadFloat3(&floats) - DirectX::XMLoadFloat3(&_rhs.floats)));

	return Vector3(f);
}

void Vector3::operator*= (float _value)
{
	floats.x *= _value;
	floats.y *= _value;
	floats.z *= _value;
}

Vector4&& Vector4::operator+ (const Vector4& _rhs)
{
	DirectX::XMFLOAT4 f;
	XMStoreFloat4(&f, (DirectX::XMLoadFloat4(&floats) - DirectX::XMLoadFloat4(&_rhs.floats)));

	return Vector4(f);
}

Vector4&& Vector4:: operator- (const Vector4& _rhs)
{
	DirectX::XMFLOAT4 f;
	XMStoreFloat4(&f, (DirectX::XMLoadFloat4(&floats) - DirectX::XMLoadFloat4(&_rhs.floats)));

	return Vector4(f);
}