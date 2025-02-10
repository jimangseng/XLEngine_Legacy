#pragma once

#include "DirectXMath.h"
#include "XLVector.h"

namespace XL
{
	namespace Math
	{
		class Matrix
		{
		public:
			Matrix() = default;

			Matrix(Vector3& _vector);
			Matrix(Vector4& _vector);

			//public:
			//	DirectX::XMMATRIX& get();
			//	void set(const DirectX::XMMATRIX& _matrix);
			//	void set(const DirectX::XMFLOAT3X3& _float3x3);
			//	void set(const DirectX::XMFLOAT4X4& _float4x4);
			//	void set(const DirectX::XMFLOAT3& _float3);
			//	void set(const DirectX::XMFLOAT4& _float4);

			//private:
			//	DirectX::XMMATRIX matrix;
			//	DirectX::XMFLOAT3X3 float3x3;
			//	DirectX::XMFLOAT4X4 float3x3;
		private:
			DirectX::XMMATRIX matrix;
		};
	}
}
