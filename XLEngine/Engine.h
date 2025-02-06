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
			: gamePlayEngine(std::make_unique<GamePlayEngine>()),
			graphicsEngine(std::make_unique<GraphicsEngine>(_hWnd))
		{
		}

	public:
		void Initialize();
		void Update();
		void Finalize();

	private:
		std::unique_ptr<GamePlayEngine> gamePlayEngine;
		std::unique_ptr<GraphicsEngine> graphicsEngine;
	};
}