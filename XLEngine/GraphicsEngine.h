#pragma once

#include <Windows.h>
#include "Renderer.h"
#include "RenderScene.h"
#include "Resources.h"
#include "GameScene.h"

namespace XL
{
	class GraphicsEngine
	{
	public:

		GraphicsEngine(HWND _hWnd)
		{
			XL::D3D11::Resources::hWnd = _hWnd;
			renderer = make_unique<XL::D3D11::Renderer>();

			scene = std::make_unique<XL::Graphics::RenderScene>();
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

	public:
		std::unique_ptr< XL::Graphics::RenderScene> scene;
	};
}

