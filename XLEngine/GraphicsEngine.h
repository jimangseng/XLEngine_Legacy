#pragma once

#include <windowsx.h>
#include "Renderer.h"
#include "RenderScene.h"
#include "Resources.h"
#include "GameScene.h"

namespace XL
{
	namespace Graphics
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
				// Todo: ResourceManager 발전시키기
				resources.hWnd = _hWnd;
				resources.Build();

				renderer = make_unique<XL::Graphics::D3D11::Renderer>();
				renderScene = std::make_unique<XL::Graphics::RenderScene>();
			}

			void Initialize(GamePlay::GameScene* _gameScene);
			void Update(GamePlay::GameScene* _gameScene);
			void Finalize();

		public:
			Graphics::RenderScene* GetScene() { return renderScene.get(); }

		private:
			XL::Graphics::D3D11::Resources& resources;
			unique_ptr<XL::Graphics::D3D11::Renderer> renderer;
			unique_ptr< XL::Graphics::RenderScene> renderScene;
		};
	}
}

