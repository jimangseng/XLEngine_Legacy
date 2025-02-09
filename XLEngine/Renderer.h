#pragma once

#include "common.h"
#include <vector>
#include "RenderScene.h"
#include "Resources.h"

using namespace DirectX;
using namespace winrt;

class Cube;

namespace XL
{
	namespace D3D11
	{
		class Renderer
		{
		public:
			Renderer() = default;
			~Renderer() = default;

			Renderer(const Renderer& rhs) = delete;
			Renderer& operator= (const Renderer& rhs) = delete;

		public:
			void Initialize();
			void Update();
			void Finalize();

		private:
			void BindResources();

		private:
			void BindView();
			void UnbindView();

		public:
			void SetCurrentScene(XL::Graphics::RenderScene* _scene);

		private:
			Resources& resources = Resources::GetInstance();

			// "XLD3DResource" ���� com_ptr�� �����ϸ�, �� �����͸� �޾ƿ� ����Ѵ�
			ID3D11DeviceContext* deviceContext;

			XL::Graphics::RenderScene* currentScene;
		};
	}
}