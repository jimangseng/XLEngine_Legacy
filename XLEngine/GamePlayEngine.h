#pragma once

#include "GameScene.h"
#include "Timer.h"
#include "Camera.h"

namespace XL
{
	namespace GamePlay
	{
		class GamePlayEngine
		{
		public:
			GamePlayEngine() = default;
			~GamePlayEngine() = default;
			GamePlayEngine(const GamePlayEngine& rhs) = delete;
			GamePlayEngine& operator= (const GamePlayEngine& rhs) = delete;

		public:
			void Initialize();
			void Update();
			void Finalize();

		public:
			XL::GamePlay::GameScene* GetScene() { return gameScene; }
			void SetScene(XL::GamePlay::GameScene* _scene) { gameScene = _scene; }


		public:
			static Timer timer;
			static Camera mainCamera;

		private:
			XL::GamePlay::GameScene* gameScene;

		};
	}
}