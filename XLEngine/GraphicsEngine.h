#pragma once

#include <windowsx.h>
#include "Renderer.h"
#include "RenderScene.h"
#include "Resources.h"
#include "GameScene.h"

namespace XL
{
	class GraphicsEngine
	{
	public:
		GraphicsEngine() = default;
		~GraphicsEngine() = default;
		GraphicsEngine(const GraphicsEngine& rhs) = delete;
		GraphicsEngine& operator= (const GraphicsEngine& rhs) = delete;

		GraphicsEngine(HWND _hWnd)
			: resources(XL::Graphics::D3D11::Resources::GetInstance())
		{
			resources.hWnd = _hWnd;
			renderer = make_unique<XL::Graphics::D3D11::Renderer>();
			scene = std::make_unique<XL::Graphics::RenderScene>();
		}

		void Initialize();
		void Update();
		void Finalize();

	public:
		void SyncScene(XL::GamePlay::GameScene* gameScene);

	private:
		XL::Graphics::D3D11::Resources& resources;
		unique_ptr<XL::Graphics::D3D11::Renderer> renderer;
		std::unique_ptr< XL::Graphics::RenderScene> scene;
	};
}

