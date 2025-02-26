#pragma once

#include "Resources.h"

namespace XL
{
	namespace GamePlay
	{
		enum class KeyCode
		{
			W,
			S,
			A,
			D,
			RButton
		};

		class InputManager
		{
		public:
			static void Update();
			static void ProcessMovement();
			static void ProcessMouseLook();
			static void Mouse();

		public:
			static KeyCode keycode;

			static float mouseX;
			static float mouseY;

		private:
			static float newMouseX;
			static float newMouseY;
			static float prevMouseX;
			static float prevMouseY;

		private:
			static float originX;
			static float originY;

		};

	}
}

