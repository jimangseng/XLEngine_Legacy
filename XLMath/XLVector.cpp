#include "XLVector.h"

using namespace DirectX;
using namespace XL::Math;


//XL::Math::Vector3::Vector3(Vector3&& _rhs)
//{
//	floats = std::move(_rhs.floats);
//}
//
//Vector3& XL::Math::Vector3::operator=(Vector3&& _rhs)
//{
//	floats = std::move(_rhs.floats);
//	return _rhs;
//}

XL::Math::Vector3::Vector3(float _x, float _y, float _z)
{
	floats.x = _x;
	floats.y = _y;
	floats.z = _z;
}

XL::Math::Vector3::Vector3(DirectX::XMFLOAT3 _floats)
{
	floats = _floats;
}

Vector3&& Vector3::operator+ (const Vector3& _rhs)
{
	DirectX::XMFLOAT3 f;
	XMStoreFloat3(&f, (DirectX::XMLoadFloat3(&floats) + DirectX::XMLoadFloat3(&_rhs.floats)));
	Vector3 v(f);
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

void XL::Math::Vector3::SetFloats(float _x, float _y, float _z)
{
	floats.x = _x;
	floats.y = _y;
	floats.z = _z;
}

XL::Math::Vector4::Vector4(float _x, float _y, float _z, float _w)
{
	floats.x = _x;
	floats.y = _y;
	floats.z = _z;
	floats.w = _w;
}

XL::Math::Vector4::Vector4(DirectX::XMFLOAT4 _floats)
{
	floats = _floats;
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

void XL::Math::Vector4::operator*=(float _value)
{
	floats.x *= _value;
	floats.y *= _value;
	floats.z *= _value;
	floats.w *= _value;
}

void XL::Math::Vector4::SetFloats(float _x, float _y, float _z, float _w)
{
	floats.x = _x;
	floats.y = _y;
	floats.z = _z;
	floats.w = _w;
}
