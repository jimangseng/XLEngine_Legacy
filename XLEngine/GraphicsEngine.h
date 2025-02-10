#pragma once

#include <windowsx.h>
#include "Renderer.h"
#include "RenderScene.h"
#include "Resources.h"

namespace XL
{
	class GraphicsEngine
	{
	public:

		GraphicsEngine(HWND _hWnd)
		{
			XL::D3D11::Resources::GetInstance().hWnd = _hWnd;
			renderer = make_unique<XL::D3D11::Renderer>();

			scene = std::make_unique<XL::Graphics::RenderScene>();
		}

		void Initialize();
		void Update();
		void Finalize();

	public:
		void SyncScene(XL::GamePlay::GameScene* gameScene);

	public:
		unique_ptr<XL::D3D11::Renderer> renderer;

	private:
		std::unique_ptr< XL::Graphics::RenderScene> scene;
	};
}

