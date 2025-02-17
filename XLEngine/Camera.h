#pragma once
#include "DirectXMath.h"
#include "InputManager.h"

using namespace DirectX;

namespace XL
{
	class Camera
	{
	public:
		Camera();

	public:
		void Update();

		static void Translate(float x, float y, float z);
		static void SetDirection(float x, float y, float z);

	public:
		static XMMATRIX viewMatrix;
		static XMVECTOR position;
		static XMVECTOR direction;
		static XMMATRIX cameraTranslation;

	private:

		XL::GamePlay::InputManager inputMAnager;
	};

}

