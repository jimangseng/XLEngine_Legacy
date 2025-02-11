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

			Vector3(const Vector3& _rhs) = delete;
			Vector3& operator= (const Vector3& _rhs) = delete;

			Vector3(Vector3&& _rhs);
			Vector3& operator= (Vector3&& _rhs);

			Vector3(float _x, float _y, float _z);
			Vector3(DirectX::XMFLOAT3 _floats);

		public:
			Vector3&& operator+ (const Vector3& _rhs);
			Vector3&& operator- (const Vector3& _rhs);
			void operator*= (float _value);

			void SetFloats(float _x, float _y, float _z);

		private:
			DirectX::XMFLOAT3 floats;
		};

		class Vector4
		{
		public:
			Vector4() = default;
			~Vector4() = default;

			Vector4(const Vector4& _rhs) = default;	// 수학 라이브러리를 본격적으로 만들기 전까지 임시로 열어둠 25. 02. 12.
			Vector4& operator= (const Vector4& _rhs) = default;	// 수학 라이브러리를 본격적으로 만들기 전까지 임시로 열어둠

			Vector4(Vector4&& _rhs) = default;	// 마찬가지로 임시로 기본 이동생성자 사용
			Vector4& operator= (Vector4&& _rhs) = default;

			Vector4(float _x, float _y, float _z, float _w);
			Vector4(DirectX::XMFLOAT4 _floats);

		public:
			Vector4&& operator+ (const Vector4& _rhs);
			Vector4&& operator- (const Vector4& _rhs);
			void operator*= (float _value);

			void SetFloats(float _x, float _y, float _z, float _w);

		public:
			DirectX::XMFLOAT4 floats;

		};
	}
}