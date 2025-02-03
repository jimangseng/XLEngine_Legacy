#pragma once

#include "common.h"
#include <vector>
#include "Scene.h"

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
			void SetCurrentScene(Scene* _scene);

		private:
			// "XLD3DResource" 에서 com_ptr로 관리하며, 생 포인터를 받아와 사용한다
			ID3D11DeviceContext* deviceContext;

			Scene* currentScene;
		};
	}
}