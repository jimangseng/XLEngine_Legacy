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
			struct Vertex
			{
				XL::Math::Vector3 localPosition;
				XMFLOAT2 UV;
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
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Finalize() override;

			virtual XL::Components::Mesh* GetMesh() override { return mesh; }

		private:
			void UpdateMatrices();

		public:
			float size;
			XL::Math::Vector4 color;
			std::vector<Vertex> vertices;
			std::vector<UINT> indices;
			std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
			const wchar_t* texturePath;

		private:
			XL::Graphics::D3D11::Resources& resources = XL::Graphics::D3D11::Resources::GetInstance();
		};
	}
}