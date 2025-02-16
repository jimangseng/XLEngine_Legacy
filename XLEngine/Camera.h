#pragma once
#include "DirectXMath.h"

using namespace DirectX;

namespace XL
{
	class Camera
	{
	public:
		Camera();

	public:
		static XMMATRIX viewMatrix;

	private:
		XMVECTOR position;
		XMVECTOR target;
	};

}

