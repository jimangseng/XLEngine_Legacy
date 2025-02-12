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
			: gamePlayEngine(GamePlay::GamePlayEngine()),
			graphicsEngine(Graphics::GraphicsEngine(_hWnd))
		{
		}

	public:
		void Initialize(GamePlay::GameScene* _gameScene);
		void Update();
		void Finalize();

	private:
		GamePlay::GamePlayEngine gamePlayEngine;
		Graphics::GraphicsEngine graphicsEngine;

		GamePlay::GameScene currentScene;
	};
}