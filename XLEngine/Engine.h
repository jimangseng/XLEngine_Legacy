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
		void Initialize();
		void Update();
		void Finalize();

	public:
		GamePlay::GameScene* GetScene() { return currentScene; }
		void SetScene(GamePlay::GameScene* _scene) { currentScene = _scene; }

	private:
		GamePlay::GamePlayEngine gamePlayEngine;
		Graphics::GraphicsEngine graphicsEngine;

		GamePlay::GameScene* currentScene;
	};
}