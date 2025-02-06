#pragma once

#include "GameScene.h"

namespace XL
{
	class GamePlayEngine
	{
	public:
		void Initialize();
		void Update();
		void Finalize();

	public:

		GamePlayEngine() = default;

	public:
		XL::GamePlay::GameScene* scene;
	};
}