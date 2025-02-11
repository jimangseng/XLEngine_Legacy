#include "XLMatrix.h"

using namespace DirectX;
using namespace XL::Math;

XL::Math::Matrix::Matrix(Vector3& _vector)
{
	//XMVECTOR translation = XMLoadFloat3(&_vector.floats);

	//matrix = XMMatrixAffineTransformation(XMVECTOR(), XMVECTOR(), XMVECTOR(), translation);
}

XL::Math::Matrix::Matrix(Vector4& _vector)
{
	//XMVECTOR translation = XMLoadFloat4(&_vector.floats);

	//matrix = XMMatrixAffineTransformation(XMVECTOR(), XMVECTOR(), XMVECTOR(), translation);
}