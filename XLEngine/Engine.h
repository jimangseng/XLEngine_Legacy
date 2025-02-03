#pragma once

#include "Renderer.h"
#include <memory>

#include <Windows.h>

using namespace std;

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
	};

	class GraphicsEngine
	{
	public:

		GraphicsEngine(HWND _hWnd)
		{
			XL::D3D11::Resources::hWnd = _hWnd;
			renderer = make_unique<XL::D3D11::Renderer>();
		}

		void Initialize();
		void Update();
		void Finalize();

	private:
		void BuildResources();


	public:
		unique_ptr<XL::D3D11::Renderer> renderer;


	public:

		GraphicsEngine() = default;
	};

	class XLEngine
	{
	public:
		XLEngine(HWND _hWnd)
			: gamePlayEngine(make_unique<GamePlayEngine>()),
			graphicsEngine(make_unique<GraphicsEngine>(_hWnd))
		{
		}

	public:
		void Initialize();
		void Update();
		void Finalize();

	private:
		unique_ptr<GamePlayEngine> gamePlayEngine;
		unique_ptr<GraphicsEngine> graphicsEngine;

	private:
		Scene* CreateScene();

	private:
		Scene* scene;
	};
}