#pragma once

#include "GameScene.h"

namespace XL
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
		XL::GamePlay::GameScene* GetScene() { return scene; }
		void SetScene(XL::GamePlay::GameScene* _scene) { scene = _scene; }
	
	private:
		XL::GamePlay::GameScene* scene;
	};
}