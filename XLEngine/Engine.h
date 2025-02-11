#pragma once

#include <Windows.h>
#include <memory>

#include "GamePlayEngine.h"
#include "GraphicsEngine.h"

#include "GameScene.h"

namespace XL
{
	class XLEngine
	{
	public:
		XLEngine(HWND _hWnd)
			: gamePlayEngine(GamePlayEngine()),
			graphicsEngine(GraphicsEngine(_hWnd))
		{
		}

	public:
		void Initialize(GamePlay::GameScene* _gameScene);
		void Update();
		void Finalize();

	private:
		void SyncScene(GamePlay::GameScene* gameScene);

	private:
		GamePlayEngine gamePlayEngine;
		GraphicsEngine graphicsEngine;
	};
}