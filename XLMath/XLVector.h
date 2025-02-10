#pragma once

#include "DirectXMath.h"
#include <utility>

namespace XL
{
	namespace Math
	{
		class Vector3
		{
		public:
			Vector3() = default;
			~Vector3() = default;

			Vector3(const Vector3&_rhs) = delete;
			Vector3& operator= (const Vector3& _rhs) = delete;

			Vector3(Vector3&& rhs)
			{
				floats = std::move(rhs.floats);
			}
			Vector3& operator= (Vector3&& _rhs)
			{
				floats = std::move(_rhs.floats);
				return _rhs;
			}

			Vector3(float x, float y, float z)
			{
				floats.x = x;
				floats.y = y;
				floats.z = z;
			}

			Vector3(DirectX::XMFLOAT3 _floats)
			{
				floats = _floats;
			}

		public:
			Vector3&& operator+ (const Vector3& _rhs);
			Vector3&& operator- (const Vector3& _rhs);
			void operator*= (float _value);

			void SetFloats(float x, float y, float z)
			{
				floats.x = x;
				floats.y = y;
				floats.z = z;
			}

		public:
			DirectX::XMFLOAT3 floats;

		};

		class Vector4
		{
		public:
			Vector4() = default;
			~Vector4() = default;

			Vector4(float x, float y, float z, float w)
			{
				floats.x = x;
				floats.y = y;
				floats.z = z;
				floats.w = w;
			}

			Vector4(DirectX::XMFLOAT4 _floats)
			{
				floats = _floats;
			}

			//Vector4(Vector4&& rhs)
			//{
			//	floats = std::move(rhs.floats);
			//}

		public:
			Vector4&& operator+ (const Vector4& _rhs);
			Vector4&& operator- (const Vector4& _rhs);

			void SetFloats(float x, float y, float z, float w)
			{
				floats.x = x;
				floats.y = y;
				floats.z = z;
				floats.w = w;
			}

		public:
			DirectX::XMFLOAT4 floats;

		};
	}
}