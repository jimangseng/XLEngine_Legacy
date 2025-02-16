#pragma once

#include "common.h"
#include <vector>
#include "RenderScene.h"
#include "Resources.h"

using namespace DirectX;
using namespace winrt;

namespace XL
{
	namespace Graphics
	{
		namespace D3D11
		{
			class Renderer
			{
			public:
				Renderer()
					:resources(Resources::GetInstance())
				{

				}
				~Renderer() = default;
				Renderer(const Renderer& rhs) = delete;
				Renderer& operator= (const Renderer& rhs) = delete;

			public:
				void Initialize();
				void Draw();
				void Finalize();

			private:
				void BindResources();

			private:
				void BindView();
				void UnbindView();

			public:
				void SetCurrentScene(RenderScene* _scene);

			private:
				RenderScene* currentScene;
				Resources& resources;
				ID3D11DeviceContext* deviceContext;			// Resources 클래스에서 com_ptr로 관리하며, 생 포인터를 받아와 사용한다
				DXGI_PRESENT_PARAMETERS presentParams;
				const float backgroundColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
			};
		}
	}
}