#pragma once

#include "Common.h"
#include <vector>
#include "GameObject.h"
#include "IRenderable.h"
#include "Resources.h"

using namespace DirectX;
using namespace std;
using namespace winrt;

namespace XL
{
	namespace GameObjects
	{
		class Cube : public GameObject, public Components::IRenderable
		{
			// 버텍스에 들어갈 데이터 구조체
			struct Vertex
			{
				XL::Math::Vector3 localPosition;
				XL::Math::Vector3 worldPosition;
				XL::Math::Vector4 color;
			};

		public:
			Cube();
			~Cube() = default;

			Cube(const Cube& _cube) = delete;
			Cube& operator= (const Cube& _cube) = delete;

			Cube(Cube&& _cube) = default;
			Cube& operator= (Cube&& _cube) = default;

			Cube(XL::Math::Vector4 _color);
			Cube(float _size, XL::Math::Vector4 _color);

		public:
			float size;
			XL::Math::Vector4 color;
			vector<Vertex> vertices;
			const int indices[3 * 2 * 6] =
			{
				0, 3, 2,
				0, 1, 3,

				0, 4, 1,
				4, 5, 1,

				3, 1, 7,
				1, 5, 7,

				4, 0, 6,
				6, 0, 2,

				5, 4, 7,
				7, 4, 6,

				6, 2, 3,
				6, 3, 7
			};

		private:
			void UpdateMatrices();

		public:
			virtual void InitializeGameObject() override;
			virtual void UpdateGameObject() override;
			virtual void FinalizeGameObject() override;

			virtual void InitializeRendeable() override;
			virtual void UpdateRenderable() override;
			virtual void DrawRenderable() override;
			virtual void FinalizeRenderable() override;


			///Render 관련
			// todo: 자원 생성, 렌더링 관련 로직이 여기 있는 것이 불합리하게 느껴지므로 수정할 것
		private:
			XL::Graphics::D3D11::Resources& resources = XL::Graphics::D3D11::Resources::GetInstance();

		protected:
			virtual void Bind() override;
			virtual void Unbind() override;

		protected:
			virtual void GetD3DResources() override;
			virtual HRESULT BuildVertexBuffer() override;
			virtual HRESULT BuildIndexBuffer() override;
			HRESULT BuildConstantBuffer();
			virtual HRESULT BuildInputLayout() override;
			virtual void BuildShader() override;
		};
	}
}